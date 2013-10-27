#include "Graphical.h"
#include "OpenGLUtil.h"

#include <cstring>

#include <glm/gtc/matrix_transform.hpp>

map<string, Graphical::GraphicalInfo> Graphical::graphicalObjects;
unsigned int Graphical::attributeCoord3d = 0;
unsigned int Graphical::attributeVColor = 1;
unsigned int Graphical::uniformMvp = 0;

Graphical::Graphical(long id, Graphical *parent) :
    id(id),
    parent(parent)
{

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

const TransformMatrix Graphical::getModel()
{
    return model;
}

void Graphical::setVertices(const string name, float *vertices)
{
    graphicalObjects[name].vertices = vertices;
}

void Graphical::setColors(const string name, float *colors)
{
    graphicalObjects[name].colors = colors;
}

void Graphical::setIndices(const string name, const short unsigned int *indices)
{
    graphicalObjects[name].indices = indices;
}

void Graphical::prepareForDraw()
{
    for( map<string, GraphicalInfo>::iterator it=graphicalObjects.begin(); it!=graphicalObjects.end(); ++it)
    {
        string name = (*it).first;
        OpenGLUtil::prepareGraphInfo(graphicalObjects[name]);
    }
}

void Graphical::draw()
{
    for( map<string, GraphicalInfo>::iterator it=graphicalObjects.begin(); it!=graphicalObjects.end(); ++it)
    {
        string name = (*it).first;
        OpenGLUtil::renderGraphInfo(graphicalObjects[name]);
    }
}
