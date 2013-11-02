#ifndef OPENGLUTIL_H
#define OPENGLUTIL_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Graphical.h"

class OpenGLUtil
{
public:
    OpenGLUtil();
    static void prepareGraphInfo(Graphical::GraphicalInfo &gi);
    static void renderGraphInfo(Graphical *graphical);
    static void configShaders(Graphical::GraphicalInfo &gi);
    static void printLog(GLuint object);
};

#endif // OPENGLUTIL_H
