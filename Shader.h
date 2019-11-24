#include <iostream>
#include <cstring>
#include <fstream>
#include <GL/glew.h>
class Shader
{
public:
    Shader();
    void CreateFromString(const char *vertexCode, const char *fragmentCode);
    void CreateFromFile(const char *vertexLocation, const char *fragmentLocation);

    // Get Locations
    GLuint GetModelProjection();
    GLuint GetModelLocation();
    GLuint GetModelView();
    GLuint GetAmbientColorLocation();
    GLuint GetAmbientIntensityLocation();
    GLuint GetDiffuseDirectionLocation();
    GLuint GetDiffuseIntensityLocation();
    GLuint GetSpecularIntensityLocation();
    GLuint GetShininessLocation();
    GLuint GetEyePositionLocation();
    void UseShader();
    void ClearShader();
    ~Shader();

private:
    std::string ReadFile(const char *fileLocation);
    void CompileShader(const char *vertexCode, const char *fragmentCode);
    void AddShader(GLuint theProgram, const char *shaderCode, GLuint shaderType);
    GLuint shaderID, uniformProjection,
        uniformModel, uniformView, uniformAmbientIntensity,
        uniformAmbientColor, uniformDiffuseDirection, uniformDiffuseIntensity,
        uniformSpecularIntensity, uniformShininess, uniformeEyePosition;
};