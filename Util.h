#ifndef UTIL_H
#define UTIL_H

#include "Position.h"
#include "TransformMatrix.h"

#include <glm/glm.hpp>

enum VERTICAL {
    UP,
    DOWN
};
enum HORIZONTAL {
    LEFT,
    RIGHT
};
enum CIRCULAR {
    CW=-1,
    CCW=1
};
enum AXIS {
    X,Y,Z
};
enum COLOR {
    R,G,B
};

class Util
{
public:
    Util();
    static glm::vec3 positionToGlmVec3(Position position);
    static glm::mat4 transformMatrixToGlmMat4(TransformMatrix transformMatrix);
};

#endif // UTIL_H
