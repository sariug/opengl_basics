#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"

const float toRadians = glm::pi<float>() / 180.0f;
GLuint shader, uniformModel, uniformProjection, uniformView;
GLfloat deltaTime =.0f;
GLfloat lastTime = .0f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
std::vector<Texture*> textureList;

Window *mainwindow = new Window;
Camera *camera;
// Vertex Shader
static const char *vShader = R"(shaders/shader.vert)";

// Pixel Shader
static const char *fShader = R"(shaders/shader.frag)";

void CreateMultiDimension()
{
	unsigned int indices[] = {0, 3, 1,
							  1, 3, 2,
							  2, 3, 0,
							  0, 1, 2};
	GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, .0f, .0f,
						  .0f, -1.0f, 1.0f, 0.5, 0.0f,
						  1.0f, -1.0f, 0.0f, 1.0f, .0f,
						  0.0f, 1.0f, 0.0f, 0.5f, 1.0f,

	};

	Mesh *dummy = new Mesh();
	dummy->createMesh(vertices, indices, 20, 12);
	meshList.push_back(dummy);
	Mesh *dummy2 = new Mesh();
	dummy2->createMesh(vertices, indices, 20, 12);
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

	camera = new Camera(glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 1.0f, .0f), 0.0f, .0f, 5.0f, 1.0f);

	textureList.push_back(new Texture("assets/photo1.png"));
	textureList.back()->LoadTexture();
	textureList.push_back(new Texture("assets/photo2.png"));
	textureList.back()->LoadTexture();

	glm::mat4 projection = glm::perspective(45.0f, mainwindow->getBufferWidth() / mainwindow->getBufferHeight(), 0.01f, 100.0f);
	// Loop until it is closed
	while (!mainwindow->shouldWindowClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now-lastTime;
		lastTime = now;
		// Get and handle user inputs
		glfwPollEvents();
		camera->keyControl(mainwindow->getKeys(),deltaTime);
		camera->mouseControl(glm::vec2(mainwindow->getXchange(),mainwindow->getYchange()));
		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetModelProjection();
		uniformView = shaderList[0]->GetModelView();
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(.0f, 0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(.0f, 1.0f, .0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
		textureList[0]->UseTexture();
		meshList[0]->renderMesh();
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, -2.f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		textureList.back()->UseTexture();
		meshList[1]->renderMesh();

		glUseProgram(0);

		mainwindow->swapBuffers();
	}

	return 0;
}