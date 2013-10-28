#ifndef GRAPHICAL_H
#define GRAPHICAL_H

#include <list>
#include <set>
#include <map>
#include <vector>

#include "Position.h"
#include "Util.h"
#include "TransformMatrix.h"

class Graphical
{
    friend class OpenGLUtil;
private:
    long id;
    string type;
    Graphical *parent;
    Position localPosition;
    float forwardspeed;
    TransformMatrix model;
    struct GraphicalInfo {
        vector<float> vertices;
        unsigned int numVertices;
        vector<float> colors;
        vector<short unsigned int> indices;
        unsigned int shaderProgram;
        unsigned int vboVertices;
        unsigned int vboColors;
        unsigned int vao;
        unsigned int ebo;
        set<Graphical*> graphicals;

        GraphicalInfo():
            numVertices(0),
            shaderProgram(0),
            vboVertices(0),
            vboColors(0),
            vao(0),
            ebo(0)
        {}
    };

    static map<string, GraphicalInfo> graphicalObjects;
    static map<string, list<Graphical*> > iGraphicals;
    static unsigned int attributeCoord3d;
    static unsigned int attributeVColor;
    static unsigned int uniformMvp;
public:    
    const static float ROTATION_SPEED = 0.0028;

    Graphical(long id, string type, Graphical *parent = NULL);
    void setParent(Graphical *parent);
    Position getPosition();
    Position setRelativePosition(Position position);
    void incForwardSpeed();
    void decForwardSpeed();
    float getForwardSpeed();
    void scale(float factor);
    void translate(Position position);
    void translateInc(Position position);
    void rotateInc(AxisVector axis, CIRCULAR circular);
    void rotate(AxisVector axis, float angle);
    TransformMatrix getModel();
    void setVertices(float *vertices, unsigned int numVertices);
    void setColors(float *colors, unsigned int size);
    void setIndices(const unsigned short *indices, unsigned int size);

    static void prepareForDraw();
    void draw();

    bool operator==(const Graphical& rhs) const
    {
        return id == rhs.id;
    }

    bool operator<(const Graphical& rhs) const
    {
        return id < rhs.id;
    }
    string getType() const;
};

#endif // GRAPHICAL_H
