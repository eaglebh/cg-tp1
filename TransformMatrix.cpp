#include "TransformMatrix.h"
#include "Util.h"

const AxisVector TransformMatrix::X_AXIS = {1.f, 0.f, 0.f};
const AxisVector TransformMatrix::Y_AXIS = {0.f, 1.f, 0.f};
const AxisVector TransformMatrix::Z_AXIS = {0.f, 0.f, 1.f};

TransformMatrix::TransformMatrix() :
    matrix(1.0f)
{
}

void TransformMatrix::scale(float factor)
{
    matrix = glm::scale(matrix, glm::vec3(factor));
}

void TransformMatrix::rotate(AxisVector axis, float angle)
{
    matrix = glm::rotate(matrix, angle, axis.value());
}

void TransformMatrix::translate(Position position)
{
    matrix = glm::translate(matrix, Util::positionToGlmVec3(position));
}

const glm::mat4 TransformMatrix::getMatrix()
{
    return matrix;
}
