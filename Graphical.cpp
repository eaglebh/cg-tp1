#include "Graphical.h"

#include <glm/gtc/matrix_transform.hpp>

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
