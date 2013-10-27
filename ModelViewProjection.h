#ifndef MODELVIEWPROJECTION_H
#define MODELVIEWPROJECTION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ModelViewProjection
{
public:
    ModelViewProjection();

private:
    glm::mat4 projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.);
    glm::mat4 model = glm::mat4(1.0);

};

#endif // MODELVIEWPROJECTION_H
