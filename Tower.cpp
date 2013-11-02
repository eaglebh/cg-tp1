#include "Tower.h"
#include "ObjLoader.h"

const char *Tower::TOWER_TYPE = "TOWER";

Tower::Tower(long id):
    HasGraphicalRepresentation(id, TOWER_TYPE)
{
    std::vector<float> v_vertices;
    std::vector<float> colors;
    std::vector<float> normals;
    std::vector<unsigned short> elements;
    ObjLoader::loadObj("tower.obj", v_vertices, normals, elements);

    graphical.setVertices(&v_vertices[0], v_vertices.size());
    graphical.setColors(&colors[0], colors.size());
    graphical.setIndices(&elements[0], elements.size());
}
