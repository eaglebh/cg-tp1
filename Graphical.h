#ifndef GRAPHICAL_H
#define GRAPHICAL_H

#include "Position.h"
#include "Util.h"
#include "TransformMatrix.h"

class Graphical
{
public:
    const static float ROTATION_SPEED = 0.0028;

    Graphical(long id, Graphical *parent = NULL);
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

    bool operator==(const Graphical& rhs) const
    {
        return id == rhs.id;
    }

    bool operator<(const Graphical& rhs) const
    {
        return id < rhs.id;
    }

private:
    long id;
    Graphical *parent;
    Position localPosition;
    float forwardspeed;
    TransformMatrix model;
};

#endif // GRAPHICAL_H
