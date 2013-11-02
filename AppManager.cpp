#include "AppManager.h"

#include "Scene.h"
#include "FalcoPeregrinus.h"
#include "Floor.h"

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

bool printou = false;

void prepareScene() {
    Position p;

    FalcoPeregrinus falco(5);
    p.setX(0.0f)->setY(0.0f)->setZ(-4.0f);
    falco.setPosition(p);

    Floor floor(7);
    p.setX(0.0f)->setY(0.0f)->setZ(0.0f);
    floor.setPosition(p);

    scene.addObject(falco.getGraphical());
    scene.addObject(floor.getGraphical());

    Graphical::prepareForDraw();
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
    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
}

void AppManager::windowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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

    initGL();

    prepareScene();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        drawScene();

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
