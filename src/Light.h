#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
    GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
    void UseLight(GLfloat ambientColorLocation, GLfloat ambientIntensityLocation, GLfloat directionLocation,GLfloat diffuseIntensityLocation);
    ~Light();

private:
    glm::vec3 color;
    GLfloat ambientIntensity;
    
    glm::vec3 direction;
    GLfloat diffuseIntensity;
};