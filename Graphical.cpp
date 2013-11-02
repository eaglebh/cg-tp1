#include "Graphical.h"
#include "OpenGLUtil.h"

#include <cstring>

#include <glm/gtc/matrix_transform.hpp>

map<string, Graphical::GraphicalInfo> Graphical::graphicalObjects;
map<string, list<Graphical*> > Graphical::iGraphicals;
unsigned int Graphical::attributeCoord3d = 0;
unsigned int Graphical::attributeVColor = 1;
unsigned int Graphical::uniformMvp = 0;


string Graphical::getType() const
{
    return type;
}

Graphical::Graphical(long id, string type, Graphical *parent) :
    id(id),
    type(type),
    parent(parent),
    forwardspeed(0)
{
    graphicalObjects[type].graphicals.insert(this);
    iGraphicals[type].push_back(this);
}

void Graphical::setParent(Graphical *parent)
{
    this->parent = parent;
}

Position Graphical::getPosition()
{    
    return parent != NULL ? parent->getPosition() + localPosition : localPosition;
}

Position Graphical::setRelativePosition(Position position)
{
    localPosition = position;
    model.translate(localPosition);
}

void Graphical::incForwardSpeed()
{
    ++forwardspeed;
}

void Graphical::decForwardSpeed()
{
    --forwardspeed;
}

float Graphical::getForwardSpeed()
{
    return forwardspeed;
}

void Graphical::scale(float factor)
{
    model.scale(factor);
}

void Graphical::translate(Position position)
{
    localPosition = position;
    model.translate(localPosition);
}

void Graphical::translateInc(Position position)
{
    localPosition += position;
    model.translate(localPosition);
}

void Graphical::rotateInc(AxisVector axis, CIRCULAR circular)
{
    model.rotate(axis, ROTATION_SPEED*circular);
}

void Graphical::rotate(AxisVector axis, float angle)
{
    model.rotate(axis, angle);
}

TransformMatrix Graphical::getModel()
{
    return model;
}

void Graphical::setVertices(float *vertices, unsigned int numVertices)
{
    vector<float> &vec = graphicalObjects[type].vertices;
    vec.insert( vec.end(), vertices, vertices+numVertices );
}

void Graphical::setColors(float *colors, unsigned int size)
{
    vector<float> &vec = graphicalObjects[type].colors;
    vec.insert( vec.end(), colors, colors+size );
}

void Graphical::setIndices(const short unsigned int *indices, unsigned int size)
{
    vector<short unsigned int> &vec = graphicalObjects[type].indices;
    vec.insert( vec.end(), indices, indices+size );
}

void Graphical::prepareForDraw()
{
    for( map<string, GraphicalInfo>::iterator it=graphicalObjects.begin(); it!=graphicalObjects.end(); ++it)
    {
        string name = (*it).first;
        OpenGLUtil::configShaders(graphicalObjects[name]);
        OpenGLUtil::prepareGraphInfo(graphicalObjects[name]);
    }
}

void Graphical::draw()
{
//    for( map<string, GraphicalInfo>::iterator it=graphicalObjects.begin(); it!=graphicalObjects.end(); ++it)
    {
//        string name = (*it).first;
        OpenGLUtil::renderGraphInfo(this);
    }
}
