#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
class Material
{
public:
    Material();
        Material(GLfloat sIntensity, GLfloat shine);
    ~Material();
    void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

private:
    GLfloat spacularIntensity;
    GLfloat shininess;
};