#include "AppManager.h"

#include "Scene.h"
#include "FalcoPeregrinus.h"

#include "ObjLoader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

GLuint myVBO;
GLuint myIndices;

AppManager::AppManager() :
    windowWidth(800), windowHeight(600) {

}

AppManager::AppManager(unsigned short width, unsigned short height) :
    windowWidth(width), windowHeight(height) {
}

/* Create a variable to hold the VBO identifier */
GLuint triangleVBO;

/* These pointers will receive the contents of our shader source code files */
string vertexSource, fragmentSource;

/* These are handles used to reference the shaders */
GLuint vertexShader, fragmentShader;


Scene scene;
int ProjectionModelviewMatrix_Loc;

float verts[] = {
    0.0f,  0.433f,  0.0f,
    0.5f, -0.433f,  0.0f,
    -0.5f, -0.433f,  0.0f
};

float rgb[] = {
    1.0f, 1.0f,  0.0f,
    1.0f, 1.0f,  0.0f,
    1.0f, 1.0f,  0.0f
};

static const GLushort idxs[] =
{
    0, 1, 2
};

GLfloat cube_vertices[] = {
    // front
    -1.0,  1.0,  1.0, // A
     1.0,  1.0,  1.0, // B
     1.0, -1.0,  1.0, // C
    -1.0, -1.0,  1.0, // D
    // back
    -1.0,  1.0, -1.0, // E
     1.0,  1.0, -1.0, // F
     1.0, -1.0, -1.0, // G
    -1.0, -1.0, -1.0, // H
};

GLfloat cube_colors[] = {
    // front colors
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    // back colors
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
};

GLushort cube_elements[] = {
    // back
    5, 6, 7,
    7, 4, 5,
    // right
    5, 1, 2,
    2, 6, 5,
    // left
    0, 4, 7,
    7, 3, 0,
    // top
    5, 4, 0,
    0, 1, 5,
    // bottom
    3, 7, 6,
    6, 2, 3,
    // front
    1, 0, 3,
    3, 2, 1,
};

unsigned int shaderProgram;
unsigned int vboVertices;
unsigned int vboColors;
unsigned int vao;
unsigned int ebo;
unsigned int attributeCoord3d=0;
unsigned int attributeVColor=1;
unsigned int uniformMvp;

unsigned int shaderProgram2;
unsigned int vboVertices2;
unsigned int vboColors2;
unsigned int vao2;
unsigned int ebo2;
unsigned int attributeCoord3d2=0;
unsigned int attributeVColor2=1;
unsigned int uniformMvp2;


void print_log(GLuint object)
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

void configShaders()
{
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

    glBindAttribLocation(shaderProgram, attributeCoord3d, "coord3d");
    glBindAttribLocation(shaderProgram, attributeVColor, "v_color");

    glLinkProgram (shaderProgram);
    GLint link_ok = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &link_ok);
    if (!link_ok) {
        fprintf(stderr, "glLinkProgram:");
        print_log(shaderProgram);
    }

    const char* uniform_name;
    uniform_name = "MVP";
    uniformMvp = glGetUniformLocation(shaderProgram, uniform_name);
    if (uniformMvp == -1) {
        fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    }
}

void configShaders2()
{
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

    shaderProgram2 = glCreateProgram();
    glAttachShader (shaderProgram2, vs);
    glAttachShader (shaderProgram2, fs);

    glBindAttribLocation(shaderProgram2, attributeCoord3d2, "coord3d");
    glBindAttribLocation(shaderProgram2, attributeVColor2, "v_color");

    glLinkProgram (shaderProgram2);
    GLint link_ok = GL_FALSE;
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &link_ok);
    if (!link_ok) {
        fprintf(stderr, "glLinkProgram:");
        print_log(shaderProgram2);
    }

    const char* uniform_name;
    uniform_name = "MVP";
    uniformMvp2 = glGetUniformLocation(shaderProgram2, uniform_name);
    if (uniformMvp2 == -1) {
        fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    }
}

void prepareGraphInfo()
{
    configShaders();

    glGenBuffers (1, &vboVertices);
    glGenBuffers (1, &vboColors);
    glGenBuffers(1, &ebo);

    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    glBindBuffer (GL_ARRAY_BUFFER, vboVertices);
    glBufferData (GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray (attributeCoord3d);
    glVertexAttribPointer (attributeCoord3d, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer (GL_ARRAY_BUFFER, vboColors);
    glBufferData (GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray (attributeVColor);
    glVertexAttribPointer (attributeVColor, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

    // Bind back to the default state.
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void renderGraphInfo()
{
    float angle = glfwGetTime() * 45;  // 45° per second
    glm::vec3 axis_z(0, 1, 1);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_z);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0, 0.0, -4.0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projection = glm::perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);

    glm::mat4 mvp = projection * view * model * anim;

    glUseProgram (shaderProgram);
    glUniformMatrix4fv(uniformMvp, 1, GL_FALSE, glm::value_ptr(mvp));

    /* Push each element in buffer_vertices to the vertex shader */
    glBindVertexArray (vao);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
    //glDrawRangeElements(GL_TRIANGLES, 0, 3, 6, GL_UNSIGNED_SHORT, NULL);
}

void prepareGraphInfo2()
{
    configShaders2();

    glGenBuffers (1, &vboVertices2);
    glBindBuffer (GL_ARRAY_BUFFER, vboVertices2);
    glBufferData (GL_ARRAY_BUFFER, 9*sizeof(float), verts, GL_STATIC_DRAW);

    glGenBuffers (1, &vboColors2);
    glBindBuffer (GL_ARRAY_BUFFER, vboColors2);
    glBufferData (GL_ARRAY_BUFFER, 9*sizeof(float), rgb, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(GLushort), idxs, GL_STATIC_DRAW);

    glGenVertexArrays (1, &vao2);
    glBindVertexArray (vao2);

    glBindBuffer (GL_ARRAY_BUFFER, vboVertices2);
    glVertexAttribPointer (attributeCoord3d2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer (GL_ARRAY_BUFFER, vboColors2);
    glVertexAttribPointer (attributeVColor2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glEnableVertexAttribArray (attributeCoord3d2);
    glEnableVertexAttribArray (attributeVColor2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);

    // Bind back to the default state.
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void renderGraphInfo2()
{
    float angle = glfwGetTime() * 45;  // 45° per second
    glm::vec3 axis_z(0, 1, 1);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_z);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0, 0.0, -4.0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projection = glm::perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);

    glm::mat4 mvp = projection * view * model * anim;

    glUseProgram (shaderProgram2);
    glUniformMatrix4fv(uniformMvp2, 1, GL_FALSE, glm::value_ptr(mvp));

    /* Push each element in buffer_vertices to the vertex shader */
    glBindVertexArray (vao2);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
    //glDrawRangeElements(GL_TRIANGLES, 0, 3, 3, GL_UNSIGNED_SHORT, NULL);
}

bool printou = false;

void prepareScene() {
    Position p;

    Graphical triangle1(1, "TRIANGLE");
    triangle1.setVertices(verts, sizeof(verts)/sizeof(verts[0]));
    triangle1.setColors(rgb, sizeof(rgb)/sizeof(rgb[0]));
    triangle1.setIndices(idxs, sizeof(idxs)/sizeof(idxs[0]));
    p.setX(-1.5f)->setY(-1.5f)->setZ(-4.0f);
    triangle1.setRelativePosition(p);

    Graphical triangle2(2, "TRIANGLE");
//    triangle2.setVertices(verts, sizeof(verts)/sizeof(verts[0]));
//    triangle2.setColors(rgb, sizeof(rgb)/sizeof(rgb[0]));
//    triangle2.setIndices(idxs, sizeof(idxs)/sizeof(idxs[0]));
    p.setX(-1.5f)->setY(1.5f)->setZ(-4.0f);
    triangle2.setRelativePosition(p);

    Graphical triangle3(3, "TRIANGLE");
//    triangle3.setVertices(verts, sizeof(verts)/sizeof(verts[0]));
//    triangle3.setColors(rgb, sizeof(rgb)/sizeof(rgb[0]));
//    triangle3.setIndices(idxs, sizeof(idxs)/sizeof(idxs[0]));
    p.setX(1.5f)->setY(1.5f)->setZ(-4.0f);
    triangle3.setRelativePosition(p);

    Graphical triangle4(4, "TRIANGLE");
//    triangle4.setVertices(verts, sizeof(verts)/sizeof(verts[0]));
//    triangle4.setColors(rgb, sizeof(rgb)/sizeof(rgb[0]));
//    triangle4.setIndices(idxs, sizeof(idxs)/sizeof(idxs[0]));
    p.setX(1.5f)->setY(-1.5f)->setZ(-4.0f);
    triangle4.setRelativePosition(p);

    Graphical cube1(6, "CUBE");
    cube1.setVertices(cube_vertices, sizeof(cube_vertices)/sizeof(cube_vertices[0]));
    cube1.setColors(cube_colors, sizeof(cube_colors)/sizeof(cube_colors[0]));
    cube1.setIndices(cube_elements, sizeof(cube_elements)/sizeof(cube_elements[0]));
    p.setX(0.0f)->setY(0.0f)->setZ(-4.0f);
    cube1.setRelativePosition(p);
    cube1.scale(0.5);

    FalcoPeregrinus falco(5);
    p.setX(0.0f)->setY(0.0f)->setZ(-4.0f);
    falco.setPosition(p);

    scene.addObject(triangle1);
    scene.addObject(triangle2);
    scene.addObject(triangle3);
    scene.addObject(triangle4);
//    scene.addObject(cube1);
        scene.addObject(falco.getGraphical());

    //    for (std::set<Graphical>::iterator it=scene.getObjectsIteratorBegin(); it!=scene.getObjectsIteratorEnd(); ++it) {
    //        Graphical graphical = *it;
    Graphical::prepareForDraw();
    //    }
}

void drawScene() {
    for (std::set<Graphical>::iterator it=scene.getObjectsIteratorBegin(); it!=scene.getObjectsIteratorEnd(); ++it) {
        Graphical graphical = *it;
        graphical.draw();
    }
}

///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void initGL()
{
//    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glDepthFunc(GL_LEQUAL);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 0);                   // background color
//    glClearStencil(0);                          // clear stencil buffer
//    glClearDepth(1.0f);                         // 0 is near, 1 is far
}

void AppManager::windowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void AppManager::loadObjFile()
{
    std::vector<float> vertices;
    std::vector<float> normals; // Won't be used at the moment.
    std::vector<GLushort> elements;
    ObjLoader::loadObj("bird.obj", vertices, normals, elements);
    cout << "res" << endl;
}

void AppManager::start(int *argcp, char **argv) throw (Exception) {

    GLFWwindow* window;

    // inicializa openGL
    if (!glfwInit())
        throw new Exception;

    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int xPos = (videoMode->width - windowWidth) / 2;
    int yPos = (videoMode->height - windowHeight) / 2;

    initGL();

    // cria janela
    window = glfwCreateWindow(windowWidth, windowHeight, "CG-Tp1", NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw new Exception;
    }

    glfwSetWindowPos(window, xPos, yPos);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, &AppManager::key_callback);

    glfwSetWindowSizeCallback(window, windowResize);

    // inicializa GLEW
    //glewExperimental = GL_TRUE;
    glewInit();
    if (!GLEW_VERSION_3_0) {
        cerr << "OpenGL 3.0 nao suportado" << endl;
        throw Exception();
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Read our .obj file
    loadObjFile();

    prepareScene();
//    prepareGraphInfo2();
//    prepareGraphInfo();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        drawScene();
//        renderGraphInfo2();
//        renderGraphInfo();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

void AppManager::key_callback(GLFWwindow* window, int key, int scancode,
                              int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
