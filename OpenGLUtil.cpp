#include "OpenGLUtil.h"
#include "Util.h"

#include <glm/gtc/type_ptr.hpp>

OpenGLUtil::OpenGLUtil()
{
}

void OpenGLUtil::prepareGraphInfo(Graphical::GraphicalInfo &gi)
{
    vector<float> &verts = gi.vertices;
    unsigned int &numVertices = gi.numVertices;
    vector<float> &rgb = gi.colors;
    vector<short unsigned int> &idxs = gi.indices;
    unsigned int &shaderProgram = gi.shaderProgram;
    unsigned int &vboVertices = gi.vboVertices;
    unsigned int &vboColors = gi.vboColors;
    unsigned int &vao = gi.vao;
    unsigned int &ebo = gi.ebo;

    glGenBuffers (1, &vboVertices);
    glBindBuffer (GL_ARRAY_BUFFER, vboVertices);
    glBufferData (GL_ARRAY_BUFFER, verts.size() * sizeof(verts[0]), &verts[0], GL_STATIC_DRAW);

    glGenBuffers (1, &vboColors);
    glBindBuffer (GL_ARRAY_BUFFER, vboColors);
    glBufferData (GL_ARRAY_BUFFER, rgb.size() * sizeof(rgb[0]), &rgb[0], GL_STATIC_DRAW);

    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glBindBuffer (GL_ARRAY_BUFFER, vboVertices);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vboColors);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
    glEnableVertexAttribArray (1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxs.size() * sizeof(idxs[0]), &idxs[0], GL_STATIC_DRAW);

    string vertexSource = Util::filetobuf("shader.vert");
    string fragmentSource = Util::filetobuf("shader.frag");

    const GLchar* vertexSourcep = vertexSource.c_str();
    const GLchar* fragmentSourcep = fragmentSource.c_str();

    unsigned int vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertexSourcep, NULL);
    glCompileShader (vs);

    unsigned int fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragmentSourcep, NULL);
    glCompileShader (fs);

    shaderProgram = glCreateProgram();
    glAttachShader (shaderProgram, vs);
    glAttachShader (shaderProgram, fs);

    glBindAttribLocation(shaderProgram, 0, "coord3d");
    glBindAttribLocation(shaderProgram, 1, "v_color");

    glLinkProgram (shaderProgram);

    const char* uniform_name;
    uniform_name = "MVP";
    Graphical::uniformMvp = glGetUniformLocation(shaderProgram, uniform_name);
    if (Graphical::uniformMvp == -1) {
        fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    }
}

void OpenGLUtil::renderGraphInfo(Graphical *graphical)
{
    Graphical::GraphicalInfo &gi = Graphical::graphicalObjects[graphical->getType()];
    unsigned int &numVertices = gi.numVertices;
    unsigned int &shaderProgram = gi.shaderProgram;
    unsigned int &vboVertices = gi.vboVertices;
    unsigned int &vboColors = gi.vboColors;
    unsigned int &vao = gi.vao;
    unsigned int &ebo = gi.ebo;

    float angle = glfwGetTime() * 45;  // 45° per second
    glm::vec3 axis_z(0, 0, 1);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_z);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0, 0.0, -4.0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 10.0f);

    glm::mat4 mvp = projection * view * model;

    glUseProgram (shaderProgram);
    glUniformMatrix4fv(Graphical::uniformMvp, 1, GL_FALSE, glm::value_ptr(mvp));

    glEnableVertexAttribArray(Graphical::attributeCoord3d);
    // Describe our vertices array to OpenGL (it can't guess its format automatically)
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glVertexAttribPointer(
                Graphical::attributeCoord3d, // attribute
                3,                 // number of elements per vertex, here (x,y,z)
                GL_FLOAT,          // the type of each element
                GL_FALSE,          // take our values as-is
                0,                 // no extra data between each position
                0                  // offset of first element
                );

    glEnableVertexAttribArray(Graphical::attributeVColor);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glVertexAttribPointer(
                Graphical::attributeVColor, // attribute
                3,                 // number of elements per vertex, here (R,G,B)
                GL_FLOAT,          // the type of each element
                GL_FALSE,          // take our values as-is
                0,                 // no extra data between each position
                0                  // offset of first element
                );

    /* Push each element in buffer_vertices to the vertex shader */
    glBindVertexArray (vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    anim = glm::rotate(glm::mat4(1.0f), angle, axis_z);
    model  = graphical->getModel().getMatrix();
    mvp = projection * view * model;
    glUniformMatrix4fv(Graphical::uniformMvp, 1, GL_FALSE, glm::value_ptr(mvp));

    int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(Graphical::attributeCoord3d);
    glDisableVertexAttribArray(Graphical::attributeVColor);
}
