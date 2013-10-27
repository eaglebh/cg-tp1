#ifndef APPMANAGER_H
#define APPMANAGER_H

#include "Exception.h"
// OpenGL headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>



class AppManager
{
private:
	int windowWidth;
	int windowHeight;
public:
	AppManager();
    AppManager(unsigned short width, unsigned short height);
    void start(int *argcp, char **argv) throw(Exception);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void windowResize(GLFWwindow *window, int width, int height);
};

#endif // APPMANAGER_H
