#include <stdio.h>
#include <cmath>
#include <string.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float toRadians = glm::pi<float>() / 180.0f;
GLuint shader, uniformModel, uniformProjection;

std::vector<Mesh *> meshList;
std::vector<Shader *> shaderList;


Window* mainwindow = new Window;
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
	GLfloat vertices[] = {-1.0f, -1.0f, 0.0f,
						  .0f, -1.0f, 1.0f,
						  1.0f, -1.0f, 0.0f,
						  0.0f, 1.0f, 0.0f

	};

	Mesh *dummy = new Mesh();
	dummy->createMesh(vertices, indices, 12, 12);
	meshList.push_back(dummy);
	Mesh *dummy2 = new Mesh();
	dummy2->createMesh(vertices, indices, 12, 12);
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

	glm::mat4 projection = glm::perspective(45.0f, mainwindow->getBufferWidth() / mainwindow->getBufferHeight(), 0.01f, 100.0f);
	// Loop until it is closed
	while (!mainwindow->shouldWindowClose())
	{
		// Get and handle user inputs
		glfwPollEvents();




		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetModelProjection();

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(.0f, 0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(.0f, 1.0f, .0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->renderMesh();
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, -2.f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		meshList[1]->renderMesh();

		glUseProgram(0);
	
		mainwindow->swapBuffers();
	}


	return 0;
}