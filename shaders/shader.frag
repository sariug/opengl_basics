#version 330

out vec4 color;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct DirectionalLight
{
vec3  color;
float ambientIntensity;
vec3  direction;
float diffuseIntensity;
};

struct Material
{
float specularIntensity;
float shininess;
};

uniform sampler2D textureSampler;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 eyeposition;

void main()
{
vec4 ambientColor  = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;

float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
vec4 diffuseColor   = vec4(directionalLight.color, 1.0f) *  diffuseFactor * directionalLight.diffuseIntensity;

vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
if (diffuseFactor > 0.0f)
{
vec3  vertexToEye    = eyeposition - FragPos;
vec3  refletedLight  = reflect(directionalLight.direction, normalize(Normal));
float specularFactor = max(dot(normalize(vertexToEye), normalize(refletedLight)), 0.0f);

if (specularFactor > 0.0f)
{
specularFactor = pow(specularFactor, material.shininess);
}

specularColor = vec4(directionalLight.color, 1.0f) *  specularFactor * material.specularIntensity;
}

color = texture(textureSampler, TexCoord) * (ambientColor + diffuseColor + specularColor);
}

