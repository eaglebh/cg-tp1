#ifndef AXISVECTOR_H
#define AXISVECTOR_H

#include <glm/glm.hpp>

struct AxisVector {
    float x;
    float y;
    float z;

    glm::vec3 value() {
        return glm::vec3(x,y,z);
    }
};

#endif // AXISVECTOR_H
