#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Light.h"
#include "Texture.h"
#include "Material.h"
const float toRadians = glm::pi<float>() / 180.0f;
GLuint shader, uniformModel, uniformProjection, uniformView, uniformAmbientColor, uniformAmbientIntensity, uniformDiffuseDirection, uniformDiffuseIntensity, uniformeEyePosition, uniformShininess, uniformSpecularIntensity;
GLfloat deltaTime = .0f;
GLfloat lastTime = .0f;

std::vector<Mesh *> meshList;
std::vector<Shader *> shaderList;
std::vector<Texture *> textureList;

Window *mainwindow = new Window;
Camera *camera;
Light *mainLight;
Material *shiny;
Material *dull;
// Vertex Shader
static const char *vShader = R"(shaders/shader.vert)";

// Pixel Shader
static const char *fShader = R"(shaders/shader.frag)";

void calcAverageNormals(unsigned int *indices, unsigned int indiceCount, GLfloat *vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}
	for (auto i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
		std::cout<<vertices[nOffset]<<" "<<
		vertices[nOffset + 1] <<" "<<
		vertices[nOffset + 2]<<std::endl;
	}
}

void CreateMultiDimension()
{
	unsigned int indices[] = {0, 3, 1,
							  1, 3, 2,
							  2, 3, 0,
							  0, 1, 2};
	//  x      y     z     u    v    n.x    n.y   n.z
	GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, .0f, .0f, 0.0f, 0.0f, 0.0f,
						  .0f, -1.0f, 1.0f, 0.5, 0.0f, 0.0f, 0.0f, 0.0f,
						  1.0f, -1.0f, 0.0f, 1.0f, .0f, 0.0f, 0.0f, 0.0f,
						  0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f

	};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh *dummy = new Mesh();
	dummy->createMesh(vertices, indices, 32, 12);
	meshList.push_back(dummy);
	Mesh *dummy2 = new Mesh();
	dummy2->createMesh(vertices, indices, 32, 12);
	meshList.push_back(dummy2);
}

void createShaders()
{
	Shader *shader1 = new Shader;
	shader1->CreateFromFile(vShader, fShader);
	shaderList.push_back(shader1);
}
int main()
{
	mainwindow->initialize();

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glEnable(GL_DEPTH_TEST);

	//CreateTriangle();
	CreateMultiDimension();
	createShaders();

	shiny = new Material(1.0f, 200);
	dull = new Material(.3f, 4);

	camera = new Camera(glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 1.0f, .0f), -90.0f, .0f, 5.0f, 2.0f);
	mainLight = new Light(1.0f, 1.0f, 1.0f, .1f,
	                      2.0f, -1.0f, -2.0f, .0f);
	textureList.push_back(new Texture("assets/photo1.png"));
	textureList.back()->LoadTexture();
	textureList.push_back(new Texture("assets/photo2.png"));
	textureList.back()->LoadTexture();

	glm::mat4 projection = glm::perspective(45.0f, mainwindow->getBufferWidth() / mainwindow->getBufferHeight(), 0.01f, 100.0f);
	// Loop until it is closed
	while (!mainwindow->shouldWindowClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;
		// Get and handle user inputs
		glfwPollEvents();
		camera->keyControl(mainwindow->getKeys(), deltaTime);
		camera->mouseControl(glm::vec2(mainwindow->getXchange(), mainwindow->getYchange()));
		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetModelProjection();
		uniformView = shaderList[0]->GetModelView();
		uniformAmbientColor = shaderList[0]->GetAmbientColorLocation();
		uniformAmbientIntensity = shaderList[0]->GetAmbientIntensityLocation();
		uniformDiffuseDirection = shaderList[0]->GetDiffuseDirectionLocation();
		uniformDiffuseIntensity = shaderList[0]->GetDiffuseIntensityLocation();
		uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
		uniformShininess = shaderList[0]->GetShininessLocation();
		uniformeEyePosition =  shaderList[0]->GetEyePositionLocation();
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-.5f, .5f, -2.0f));
		 model = glm::scale(model, glm::vec3(.3f, .3f, .3f));
		model = glm::rotate(model, 15.0f * toRadians, glm::vec3(.0f, 1.0f, .0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
		mainLight->UseLight(uniformAmbientColor, uniformAmbientIntensity,
							uniformDiffuseDirection, uniformDiffuseIntensity);
		
		auto eye = camera->getCameraPosition();
		glUniform3f(uniformeEyePosition, eye.x, eye.y, eye.z);
		shiny->UseMaterial(uniformSpecularIntensity,uniformShininess);
	    //dull->UseMaterial(uniformSpecularIntensity,uniformShininess);

		textureList[0]->UseTexture();
		meshList[0]->renderMesh();
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(.5f, -.5f, -2.0f));
		 model = glm::scale(model, glm::vec3(.3f, .3f, .3f));
		model = glm::rotate(model, 15.0f * toRadians, glm::vec3(.0f, 1.0f, .0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		textureList.back()->UseTexture();
		meshList[1]->renderMesh();

		glUseProgram(0);

		mainwindow->swapBuffers();
	}

	return 0;
}