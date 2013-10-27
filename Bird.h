#ifndef BIRD_H
#define BIRD_H

#include "HasGraphicalRepresentation.h"

class Bird : public HasGraphicalRepresentation
{
private:
    const static float MIN_SPEED = 0;
    const static char *BIRD_TYPE;
    float wingsMovementSpeed;

protected:
    float maxSpeed;

public:
    Bird(long id);
    Bird(long id, float maxSpeed);
    void incSpeed();
    void yawn(CIRCULAR value);
    void pitch(CIRCULAR value);
    void roll(CIRCULAR value);
};

#endif // BIRD_H
