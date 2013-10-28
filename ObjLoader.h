#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class ObjLoader
{
public:
    ObjLoader();
    static void loadObj(const char *filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements);
};

#endif // OBJLOADER_H
