#include "Material.h"

Material::Material()
{
    spacularIntensity = shininess= 0;
}

Material::Material(GLfloat sIntensity, GLfloat shine):shininess(shine), spacularIntensity(sIntensity)
{

}
void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
    glUniform1f(shininessLocation, this->shininess);
    glUniform1f(specularIntensityLocation, this->spacularIntensity);
    }

Material::~Material()
{
}