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
    static void renderGraphInfo(Graphical::GraphicalInfo &gi);
};

#endif // OPENGLUTIL_H
