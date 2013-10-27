#include "Position.h"

#include <sstream>
#include <glm/gtc/swizzle.hpp>

Position::Position(){

}

float Position::getX() {
    return glm::swizzle(position, glm::X);
}

float Position::getY() {
    return glm::swizzle(position, glm::Y);
}

float Position::getZ() {
    return glm::swizzle(position, glm::Z);
}

float Position::getW() {
    return glm::swizzle(position, glm::W);
}

Position *Position::setX(float value) {
    position = glm::vec4(value, glm::swizzle(position, glm::Y,glm::Z,glm::W));
    return this;
}

Position *Position::setY(float value) {
    position = glm::vec4(getX(), value, glm::swizzle(position, glm::Z,glm::W));
    return this;
}

Position *Position::setZ(float value) {
    position = glm::vec4(glm::swizzle(position, glm::X,glm::Y), value, getW());
    return this;
}

Position *Position::setW(float value) {
    position = glm::vec4(glm::swizzle(position, glm::X,glm::Y,glm::Z), value);
    return this;
}

Position::Position(const Position &source)
{
    position = source.position;
}

Position &Position::operator=(const Position &source)
{
    position = source.position;
    return *this;
}

Position &Position::operator+=(const Position &rhs) {
    position += rhs.position;
    return *this;
}

const Position Position::operator+(const Position &other) const {
    Position result = *this;
    result += other;
    return result;
}

const string Position::toString()
{
    stringstream ss;
    ss << "x=" << getX() << " y=" << getY() << " z=" << getZ();
    return ss.str();
}
