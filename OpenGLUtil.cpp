#include "OpenGLUtil.h"
#include "Util.h"

#include <glm/gtc/type_ptr.hpp>

OpenGLUtil::OpenGLUtil()
{
}

void OpenGLUtil::configShaders(Graphical::GraphicalInfo &gi)
{
    unsigned int &shaderProgram = gi.shaderProgram;
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

    glBindAttribLocation(shaderProgram, Graphical::attributeCoord3d, "coord3d");
    glBindAttribLocation(shaderProgram, Graphical::attributeVColor, "v_color");

    glLinkProgram (shaderProgram);
    GLint link_ok = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &link_ok);
    if (!link_ok) {
        fprintf(stderr, "glLinkProgram:");
        printLog(shaderProgram);
    }

    const char* uniform_name;
    uniform_name = "MVP";
    Graphical::uniformMvp = glGetUniformLocation(shaderProgram, uniform_name);
    if (Graphical::uniformMvp == -1) {
        fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    }
}

void OpenGLUtil::prepareGraphInfo(Graphical::GraphicalInfo &gi)
{
    vector<float> &verts = gi.vertices;
    vector<float> &rgb = gi.colors;
    vector<short unsigned int> &idxs = gi.indices;
    unsigned int &vboVertices = gi.vboVertices;
    unsigned int &vboColors = gi.vboColors;
    unsigned int &vao = gi.vao;
    unsigned int &ebo = gi.ebo;

    glGenBuffers (1, &vboVertices);
    glGenBuffers (1, &vboColors);
    glGenBuffers(1, &ebo);

    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    glBindBuffer (GL_ARRAY_BUFFER, vboVertices);
    GLuint vertsSize = verts.size() * sizeof(verts[0]);
    glBufferData (GL_ARRAY_BUFFER, vertsSize, &verts[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray (Graphical::attributeCoord3d);
    glVertexAttribPointer (Graphical::attributeCoord3d, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer (GL_ARRAY_BUFFER, vboColors);
    GLuint rgbSize =rgb.size() * sizeof(rgb[0]);
    glBufferData (GL_ARRAY_BUFFER, rgbSize, &rgb[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray (Graphical::attributeVColor);
    glVertexAttribPointer (Graphical::attributeVColor, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    GLuint idxsSize = idxs.size() * sizeof(idxs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxsSize, &idxs[0], GL_STATIC_DRAW);

    // Bind back to the default state.
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLUtil::renderGraphInfo(Graphical *graphical)
{
    Graphical::GraphicalInfo &gi = Graphical::graphicalObjects[graphical->getType()];
    unsigned int &shaderProgram = gi.shaderProgram;
    unsigned int &vao = gi.vao;

    float angle = glfwGetTime() * 15;  // 45° per second
    glm::vec3 axis_z(1, 1, 1);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_z);

    glm::mat4 model = graphical->getModel().getMatrix();
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projection = glm::perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);

    glm::mat4 mvp = projection * view * model;

    glUseProgram (shaderProgram);
    glUniformMatrix4fv(Graphical::uniformMvp, 1, GL_FALSE, glm::value_ptr(mvp));

    /* Push each element in buffer_vertices to the vertex shader */
    glBindVertexArray (vao);

//    anim = glm::rotate(glm::mat4(1.0f), angle, axis_z);
//    model  = graphical->getModel().getMatrix();
//    mvp = projection * view * model * anim;
//    glUniformMatrix4fv(Graphical::uniformMvp, 1, GL_FALSE, glm::value_ptr(mvp));

    int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

}

void OpenGLUtil::printLog(GLuint object)
{
    GLint log_length = 0;
    if (glIsShader(object))
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else if (glIsProgram(object))
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else {
        fprintf(stderr, "printlog: Not a shader or a program\n");
        return;
    }

    char* log = (char*)malloc(log_length);

    if (glIsShader(object))
        glGetShaderInfoLog(object, log_length, NULL, log);
    else if (glIsProgram(object))
        glGetProgramInfoLog(object, log_length, NULL, log);

    fprintf(stderr, "%s", log);
    free(log);
}
