#include "Util.h"

Util::Util()
{
}

glm::vec3 Util::positionToGlmVec3(Position position)
{
    return glm::vec3(position.getX(), position.getY(), position.getZ());
}

glm::mat4 Util::transformMatrixToGlmMat4(TransformMatrix transformMatrix)
{
    return transformMatrix.getMatrix();
}
