#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <glm/glm.hpp>

using namespace std;

class Position
{
private:
    glm::vec4 position;
public:
    Position();

    float getX();
    float getY();
    float getZ();
    float getW();
    Position *setX(float value);
    Position *setY(float value);
    Position *setZ(float value);
    Position *setW(float value);
    Position(const Position &source);
    Position &operator= (const Position &source);
    Position &operator+=(const Position &rhs);
    const Position operator+(const Position &other) const;
    const string toString();
};

#endif // POSITION_H
