#include "AppManager.h"

#include "Scene.h"


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


Scene scene;
int ProjectionModelviewMatrix_Loc;

void prepareDrawWithShader() {
    const unsigned int shaderAttribute = 0;

    const float NUM_OF_VERTICES_IN_DATA=3;

    /* Vertices of a triangle (counter-clockwise winding) */
    float data[3][3] = {
        {  0.0, 0.5, 0.0   },
        { -0.5, -0.5, 0.0  },
        {  0.5, -0.5, 0.0  }
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
    glBindAttribLocation(shaderProgram, shaderAttribute, "vp");

    /* Link shader program*/
    glLinkProgram(shaderProgram);
    /*-------------------------------------------------------------------------------------------------------*/

    Graphical triangle(0);
    Position p0;
    p0.setX(-0.5f)->setY(0.0f)->setZ(0.0f);
    triangle.setRelativePosition(p0);
    scene.addObject(triangle);

    ProjectionModelviewMatrix_Loc=glGetUniformLocation(shaderProgram, "MVP");

}

glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
glm::mat4 View = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));

void drawWithShader() {

    /* Set shader program as being actively used */
    glUseProgram(shaderProgram);

    /* Set background colour to BLACK */
    glClearColor(0.0, 0.0, 0.2, 1.0);

    //Clear all the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    for (std::set<Graphical>::iterator it=scene.getObjectsIteratorBegin(); it!=scene.getObjectsIteratorEnd(); ++it) {
        //std::cout << "pos= " << ((Graphical)*it).getPosition().toString() << endl;
        glm::mat4 Model = Util::transformMatrixToGlmMat4(((Graphical)*it).getModel());

        glm::mat4 MVP = Projection * View * Model;
        glUniformMatrix4fv(ProjectionModelviewMatrix_Loc, 1, GL_FALSE, glm::value_ptr(MVP));
    }



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

float colors[] = {
    1.0f, 0.0f,  0.0f,
    1.0f, 0.0f,  0.0f,
    1.0f, 0.0f,  0.0f
};

bool printou = false;

unsigned int shader_programme = 0;
GLuint vbo_vertices = 0;
GLuint vbo_colors = 0;
GLuint vao = 0;
GLint attribute_coord3d, attribute_v_color;
GLint uniform_mvp;

void simpleLoad(){
    //const unsigned int shaderAttribute = 0;

    glGenBuffers (1, &vbo_vertices);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);
    //glVertexAttribPointer(shaderAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glEnableVertexAttribArray(shaderAttribute);

    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glGenBuffers (1, &vbo_colors);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_colors);
    glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), colors, GL_STATIC_DRAW);


    string vertexSource = filetobuf("shader.vert");
    string fragmentSource = filetobuf("shader.frag");

    const GLchar* vertexSourcep = vertexSource.c_str();
    const GLchar* fragmentSourcep = fragmentSource.c_str();

    unsigned int vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertexSourcep, NULL);
    glCompileShader (vs);
    unsigned int fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragmentSourcep, NULL);
    glCompileShader (fs);

    shader_programme = glCreateProgram();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);

    //glBindAttribLocation(shader_programme, shaderAttribute, "vp");

    glLinkProgram (shader_programme);

    const char* attribute_name;
    attribute_name = "coord3d";
    attribute_coord3d = glGetAttribLocation(shader_programme, attribute_name);
    if (attribute_coord3d == -1) {
        fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    }
    attribute_name = "v_color";
    attribute_v_color = glGetAttribLocation(shader_programme, attribute_name);
    if (attribute_v_color == -1) {
        fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    }
    const char* uniform_name;
    uniform_name = "MVP";
    uniform_mvp = glGetUniformLocation(shader_programme, uniform_name);
    if (uniform_mvp == -1) {
        fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    }


    Graphical triangle(0);
    Position p0;
    p0.setX(-0.5f)->setY(0.0f)->setZ(0.0f);
    triangle.setRelativePosition(p0);
    scene.addObject(triangle);

}

void simpleDraw(){
    // wipe the drawing surface clear
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   float angle = glfwGetTime() * 45;  // 45° per second
    glm::vec3 axis_z(0, 0, 1);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_z);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 10.0f);

    glm::mat4 mvp = projection * view * model * anim;

    glUseProgram (shader_programme);
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

    glEnableVertexAttribArray(attribute_coord3d);
    // Describe our vertices array to OpenGL (it can't guess its format automatically)
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(
                attribute_coord3d, // attribute
                3,                 // number of elements per vertex, here (x,y,z)
                GL_FLOAT,          // the type of each element
                GL_FALSE,          // take our values as-is
                0,                 // no extra data between each position
                0                  // offset of first element
                );

    glEnableVertexAttribArray(attribute_v_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glVertexAttribPointer(
                attribute_v_color, // attribute
                3,                 // number of elements per vertex, here (R,G,B)
                GL_FLOAT,          // the type of each element
                GL_FALSE,          // take our values as-is
                0,                 // no extra data between each position
                0                  // offset of first element
                );

    /* Push each element in buffer_vertices to the vertex shader */
    glBindVertexArray (vao);
//    int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
//    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays (GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(attribute_coord3d);
    glDisableVertexAttribArray(attribute_v_color);
    //    for (std::set<Graphical>::iterator it=scene.getObjectsIteratorBegin(); it!=scene.getObjectsIteratorEnd(); ++it) {
    //        //std::cout << "pos= " << ((Graphical)*it).getPosition().toString() << endl;
    //        glm::mat4 Model = Util::transformMatrixToGlmMat4(((Graphical)*it).getModel());
    //        Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
    //        glm::mat4 MVP = Projection * View * Model;
    //        glUniformMatrix4fv(ProjectionModelviewMatrix_Loc, 1, GL_FALSE, glm::value_ptr(MVP));
    //    }



}

void loadData()
{
    GLfloat vertexData[] = {0, 0.5, 0,  0.5, -0.5, 0,   -0.5, -0.5, 0};
    GLubyte indexData[] = {0, 1, 2};

    glGenBuffers(1, &myVBO);
    glGenBuffers(1, &myIndices);

    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBufferData(GL_ARRAY_BUFFER, 9 *sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLubyte), indexData, GL_STATIC_DRAW);
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
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

    // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
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

    simpleLoad();
    //prepareDrawWithShader();

    /* Render here */
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        simpleDraw();
        //        drawWithShader();

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
