#include "Bird.h"

const char *Bird::BIRD_TYPE = "BIRD";

Bird::Bird(long id) :
    HasGraphicalRepresentation(id, BIRD_TYPE),
    // velocidade maxima do falcao peregrino http://en.wikipedia.org/wiki/Peregrine_Falcon
    maxSpeed(57)
{
}

Bird::Bird(long id, float maxSpeed):
    HasGraphicalRepresentation(id, BIRD_TYPE),
    maxSpeed(maxSpeed)
{
}

void Bird::incSpeed()
{
    this->graphical.incForwardSpeed();
}

void Bird::yawn(CIRCULAR value)
{
    this->graphical.rotate(TransformMatrix::Y_AXIS, value);
}

void Bird::pitch(CIRCULAR value)
{
    this->graphical.rotate(TransformMatrix::X_AXIS, value);
}

void Bird::roll(CIRCULAR value)
{
    this->graphical.rotate(TransformMatrix::Z_AXIS, value);
}
