#include "AppManager.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

GLuint myVBO;
GLuint myIndices;

AppManager::AppManager() :
    windowWidth(800), windowHeight(600) {

}

AppManager::AppManager(unsigned short width, unsigned short height) :
    windowWidth(width), windowHeight(height) {
}

string filetobuf(const char* filename) {
    ifstream ifs(filename);
    string line;
    stringstream ss;

    if (ifs.is_open())
    {
        while ( getline (ifs,line) )
        {
            ss << line << endl;
        }
        ifs.close();
    }

    return ss.str();
}

/* Create a variable to hold the VBO identifier */
GLuint triangleVBO;

/* This is a handle to the shader program */
GLuint shaderProgram;

/* These pointers will receive the contents of our shader source code files */
string vertexSource, fragmentSource;

/* These are handles used to reference the shaders */
GLuint vertexShader, fragmentShader;

void prepareDrawWithShader() {
    const unsigned int shaderAttribute = 0;

    const float NUM_OF_VERTICES_IN_DATA=3;

    /* Vertices of a triangle (counter-clockwise winding) */
    float data[3][3] = {
        {  0.0, 1.0, 0.0   },
        { -1.0, -1.0, 0.0  },
        {  1.0, -1.0, 0.0  }
    };

    /*---------------------- Initialise VBO - (Note: do only once, at start of program) ---------------------*/
    /* Create a new VBO and use the variable "triangleVBO" to store the VBO id */
    glGenBuffers(1, &triangleVBO);

    /* Make the new VBO active */
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    /* Upload vertex data to the video device */
    glBufferData(GL_ARRAY_BUFFER, NUM_OF_VERTICES_IN_DATA * 3 * sizeof(float), data, GL_STATIC_DRAW);

    /* Specify that our coordinate data is going into attribute index 0(shaderAttribute), and contains three floats per vertex */
    glVertexAttribPointer(shaderAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /* Enable attribute index 0(shaderAttribute) as being used */
    glEnableVertexAttribArray(shaderAttribute);

    /* Make the new VBO active. */
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    /*-------------------------------------------------------------------------------------------------------*/

    /*--------------------- Load Vertex and Fragment shaders from files and compile them --------------------*/
    /* Read our shaders into the appropriate buffers */
    vertexSource = filetobuf("shader.vert");
    fragmentSource = filetobuf("shader.frag");

    /* Assign our handles a "name" to new shader objects */
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    /* Associate the source code buffers with each handle */
    const GLchar* vertexSourcep = vertexSource.c_str();
    const GLchar* fragmentSourcep = fragmentSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourcep, 0);
    glShaderSource(fragmentShader, 1, &fragmentSourcep, 0);

    /* Compile our shader objects */
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    /*-------------------------------------------------------------------------------------------------------*/

    /*-------------------- Create shader program, attach shaders to it and then link it ---------------------*/
    /* Assign our program handle a "name" */
    shaderProgram = glCreateProgram();

    /* Attach our shaders to our program */
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    /* Bind attribute index 0 (shaderAttribute) to in_Position*/
    /* "in_Position" will represent "data" array's contents in the vertex shader */
    glBindAttribLocation(shaderProgram, shaderAttribute, "in_Position");

    /* Link shader program*/
    glLinkProgram(shaderProgram);
    /*-------------------------------------------------------------------------------------------------------*/

}

void drawWithShader() {    
    /* Set shader program as being actively used */
    glUseProgram(shaderProgram);

    /* Set background colour to BLACK */
    glClearColor(0.0, 0.0, 0.2, 1.0);

    /* Clear background with BLACK colour */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Actually draw the triangle, giving the number of vertices provided by invoke glDrawArrays
       while telling that our data is a triangle and we want to draw 0-3 vertexes
    */
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

float points[] = {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
};

const char* vertex_shader =
        "#version 130\n"
        "in vec3 vp;\n"
        "void main () {\n"
        "  gl_Position = vec4 (vp, 1.0);\n"
        "}";

const char* fragment_shader =
        "#version 130\n"
        "out vec4 frag_colour;\n"
        "void main () {\n"
        "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);\n"
        "}";
bool printou = false;
void simpleDraw(){
    GLuint vbo = 0;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    const GLchar* vertexSourcep = vertexSource.c_str();
    const GLchar* fragmentSourcep = fragmentSource.c_str();

    unsigned int vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertexSourcep, NULL);
    glCompileShader (vs);
    unsigned int fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragmentSourcep, NULL);
    glCompileShader (fs);

    unsigned int shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);


    // wipe the drawing surface clear
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (shader_programme);
    glBindVertexArray (vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays (GL_TRIANGLES, 0, 3);

}

void drawCube(float x)
{
    // vertex coords array for glDrawArrays() =====================================
    // A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
    // of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
    // vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
    // array is 108 floats (36 * 3 = 108).
    GLfloat vertices[]  = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
                            -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

                            1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
                            1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

                            1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
                            -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

                            -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
                            -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

                            -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
                            1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

                            1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
                            -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

    // normal array
    GLfloat normals[]   = { 0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
                            0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

                            1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
                            1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

                            0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
                            0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

                            -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
                            -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

                            0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
                            0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

                            0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
                            0, 0,-1,   0, 0,-1,   0, 0,-1 };    // v6-v5-v4

    // color array
    GLfloat colors[]    = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
                            1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

                            1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
                            0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

                            1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
                            0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

                            1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
                            0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

                            0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
                            1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

                            0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
                            0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4


    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    //    glNormalPointer(GL_FLOAT, 0, normals1);
    //    glColorPointer(3, GL_FLOAT, 0, colors1);
    //    glVertexPointer(3, GL_FLOAT, 0, g_vertex_buffer_data);

    GLfloat vertexData[] = {0, 2, 0,  -2, -2, 0,   2, -2, 0};
    GLubyte indexData[] = {0, 1, 2};

    GLuint myVBO = 0;
    GLuint myIndices;

    glGenBuffers(1, &myVBO);
    glGenBuffers(1, &myIndices);

    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);


    glPushMatrix();
    glTranslatef(-0.2, 0, 0);                  // move to upper-right corner
    glScalef(0.2,0.2,0.2);

    //    glDrawArrays(GL_TRIANGLES, 0, 36);


    glLoadIdentity();
    glColor3f(1, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndices);

    glEnableVertexAttribArray(0);                                               //ENABLE VERTEX POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);      // VERTEX POSITION POINTER

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
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
    //    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    //    glEnable(GL_DEPTH_TEST);
    //    glEnable(GL_LIGHTING);
    //    glEnable(GL_TEXTURE_2D);
    //    glEnable(GL_CULL_FACE);

    // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    //    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //    glEnable(GL_COLOR_MATERIAL);

    //    glClearColor(0, 0, 0, 0);                   // background color
    //    glClearStencil(0);                          // clear stencil buffer
    //    glClearDepth(1.0f);                         // 0 is near, 1 is far
    //    glDepthFunc(GL_LEQUAL);
}

void loadData()
{
    GLfloat vertexData[] = {0, 2, 0,  -2, -2, 0,   2, -2, 0};
    GLubyte indexData[] = {0, 1, 2};

    glGenBuffers(1, &myVBO);
    glGenBuffers(1, &myIndices);

    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
}

void drawScene()
{
    glLoadIdentity();
    glTranslatef(0, 0, -10);
    //glRotatef(rotZ, 0, 0, 1);

    glColor3f(1, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndices);

    glEnableVertexAttribArray(0);                                               //ENABLE VERTEX POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);      // VERTEX POSITION POINTER

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);
}


void AppManager::start(int *argcp, char **argv) throw (Exception) {

    GLFWwindow* window;

    // inicializa openGL
    if (!glfwInit())
        throw new Exception;

    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    //    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int xPos = (videoMode->width - windowWidth) / 2;
    int yPos = (videoMode->height - windowHeight) / 2;

    initGL();

    // cria janela
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw new Exception;
    }

    glfwSetWindowPos(window, xPos, yPos);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, &AppManager::key_callback);

    // inicializa GLEW
    //glewExperimental = GL_TRUE;
    glewInit();
    if (!GLEW_VERSION_3_0) {
        cerr << "OpenGL 3.0 nao suportado" << endl;
        throw Exception();
    }

    vertexSource = filetobuf("shader.vert");
    fragmentSource = filetobuf("shader.frag");

    if(!printou) {
    cout << "v1\n" << vertex_shader << endl;
    cout << "v2\n" << vertexSource << endl;
    cout << "f2\n" << fragment_shader << endl;
    cout << "f2\n" << fragmentSource << endl;
    printou = true;
    }

    prepareDrawWithShader();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, ratio, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
        //glLoadIdentity();
        //        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

        //        glBegin(GL_TRIANGLES);
        //        glColor3f(0.f, 1.f, 0.f);
        //        glVertex3f(-0.3f, -0.4f, 0.f);
        //        glColor3f(0.f, 1.f, 0.f);
        //        glVertex3f(0.3f, -0.4f, 0.f);
        //        glColor3f(0.f, 1.f, 0.f);
        //        glVertex3f(0.f, 0.3f, 0.f);
        //        glEnd();

        //        glRotatef(-(float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        //        glTranslatef(-0.5f, 0.f, 0.f);
        //        glBegin(GL_TRIANGLES);
        //        glColor3f(1.f, 0.f, 0.f);
        //        glVertex3f(-0.2f, -0.2f, 0.f);
        //        glColor3f(0.f, 1.f, 0.f);
        //        glVertex3f(0.2f, -0.2f, 0.f);
        //        glColor3f(0.f, 0.f, 1.f);
        //        glVertex3f(0.f, 0.2f, 0.f);
        //        glEnd();

        //drawCube(0);
        drawWithShader();
        //simpleDraw();

        //loadData();
        //drawScene();


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
