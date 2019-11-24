#include "Light.h"

Light::Light()
{
    color = glm::vec3(1.0f);
    this->ambientIntensity = 1.0f;
}
Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity) : ambientIntensity(aIntensity)
{
    color = glm::vec3(red, green, blue);
}
void Light::UseLight(GLfloat ambientColorLocation, GLfloat ambientIntensityLocation)
{
    glUniform3f(ambientColorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, this->ambientIntensity);
}
Light::~Light() {}
