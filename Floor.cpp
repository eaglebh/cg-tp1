#include "Floor.h"
#include "ObjLoader.h"

Floor::Floor(long id) :
    HasGraphicalRepresentation(id, "FLOOR")
{
    std::vector<float> v_vertices;
    std::vector<float> colors;
    std::vector<float> normals;
    std::vector<unsigned short> elements;
    ObjLoader::loadObj("floor.obj", v_vertices, normals, elements);

    for (std::vector<float>::iterator it = v_vertices.begin() ; it != v_vertices.end(); ++it) {
        colors.push_back(1.0f);
    }


    graphical.setVertices(&v_vertices[0], v_vertices.size());
    graphical.setColors(&colors[0], colors.size());
    graphical.setIndices(&elements[0], elements.size());
}
