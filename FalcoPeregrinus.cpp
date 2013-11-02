#include "FalcoPeregrinus.h"
#include "ObjLoader.h"


FalcoPeregrinus::FalcoPeregrinus(long id) :
    // velocidade maxima do falcao peregrino http://en.wikipedia.org/wiki/Peregrine_Falcon
    Bird(id, 57)
{
    float colorsorig[] = {
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f,
        1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.0f
    };


    std::vector<float> v_vertices;
    std::vector<float> colors;
    std::vector<float> normals;
    std::vector<unsigned short> elements;
    ObjLoader::loadObj("bird.obj", v_vertices, normals, elements);

    for (std::vector<float>::iterator it = v_vertices.begin() ; it != v_vertices.end(); ++it) {
        colors.push_back(0.5f);
    }

    graphical.setVertices(&v_vertices[0], v_vertices.size());
    graphical.setColors(&colors[0], colors.size());
    graphical.setIndices(&elements[0], elements.size());

}
