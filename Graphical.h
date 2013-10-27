#ifndef GRAPHICAL_H
#define GRAPHICAL_H

#include <map>

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
        float *vertices;
        float *colors;
        const short unsigned int *indices;
        unsigned int shaderProgram;
        unsigned int vboVertices;
        unsigned int vboColors;
        unsigned int vao;
        unsigned int ebo;
    };

    static map<string, GraphicalInfo> graphicalObjects;
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
    void scale(AxisVector axis, CIRCULAR circular);
    void translate(Position position);
    void translateInc(Position position);
    void rotateInc(AxisVector axis, CIRCULAR circular);
    void rotate(AxisVector axis, float angle);
    const TransformMatrix getModel();
    static void setVertices(const string name, float *vertices);
    static void setColors(const string name, float *colors);
    static void setIndices(const string name, const unsigned short *indices);

    void prepareForDraw();
    void draw();

    bool operator==(const Graphical& rhs) const
    {
        return id == rhs.id;
    }

    bool operator<(const Graphical& rhs) const
    {
        return id < rhs.id;
    }
};

#endif // GRAPHICAL_H
