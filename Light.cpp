#include "Light.h"

Light::Light()
{
    color = glm::vec3(1.0f);
    this->ambientIntensity = 1.0f;
    direction = glm::vec3(0.0f);
    this->diffuseIntensity = 0.0f;
}
Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity) : ambientIntensity(aIntensity)
{
    color = glm::vec3(red, green, blue);
    direction = glm::vec3(0.0f);
    this->diffuseIntensity = 0.0f;
}
Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
             GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity) : ambientIntensity(aIntensity), diffuseIntensity(dIntensity)
{
    color = glm::vec3(red, green, blue);
    direction = glm::vec3(xDir, yDir, zDir);
}

void Light::UseLight(GLfloat ambientColorLocation, GLfloat ambientIntensityLocation, GLfloat directionLocation,GLfloat diffuseIntensityLocation)
{
    glUniform3f(ambientColorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, this->ambientIntensity);
    
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(diffuseIntensityLocation, this->diffuseIntensity);
}
Light::~Light() {}
