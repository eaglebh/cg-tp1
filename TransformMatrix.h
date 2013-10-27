#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "AxisVector.h"
#include "Position.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformMatrix
{
public:
    const static AxisVector X_AXIS;
    const static AxisVector Y_AXIS;
    const static AxisVector Z_AXIS;
    TransformMatrix();
    void scale(float factor);
    void rotate(AxisVector axis, float angle);
    void translate(Position position);
    const glm::mat4 getMatrix();
private:
    glm::mat4 matrix;
};

#endif // TRANSFORMMATRIX_H
