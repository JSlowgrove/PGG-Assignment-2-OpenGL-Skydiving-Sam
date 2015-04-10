#include "Model.h"

#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Model::Model()
{
	// Initialise variables
	_VAO = 0;
	_program = 0;
	_shaderModelMatLocation = _shaderViewMatLocation = _shaderProjMatLocation = 0;
	_numVertices = 0;

	// Create the model
	InitialiseVAO();
	// Create the shaders
	InitialiseShaders();
}

Model::~Model()
{
	// TODO: destroy VAO, shaders etc
}

void Model::InitialiseVAO()
{
	Object* obj = new Object("obj/train.obj");
	_VAO = obj->getVBO();
	_numVertices = obj->getNumberOfVertices();
}

void Model::InitialiseShaders()
{
	Shader* shader = new Shader("shaders/vertexShader.txt", "shaders/fragmentShader.txt");
	_program = shader->getShaderProgram();
	_shaderModelMatLocation = shader->getModelMatrixLocation();
	_shaderViewMatLocation = shader->getViewMatrixLocation();
	_shaderProjMatLocation = shader->getShaderProjectionMatrixLocation();
}


void Model::Update(float deltaTs)
{
	// update the rotation angle of our cube
	_rotation.y += deltaTs * 0.5f;
	while (_rotation.y > (3.14159265358979323846 * 2.0))
	{
		_rotation.y -= (float)(3.14159265358979323846 * 2.0);
	}

	// Build the model matrix!
	// First we start with an identity matrix
	// This is created with the command: glm::mat4(1.0f)
	// Next, we translate this matrix according to the object's _position vector:
	_modelMatrix = glm::translate(glm::mat4(1.0f), _position);
	// Next, we rotate this matrix in the y-axis by the object's y-rotation:
	_modelMatrix = glm::rotate(_modelMatrix, _rotation.y, glm::vec3(0, 1, 0));
	// Scale the matrix to scale the object:
	_modelMatrix = glm::scale(_modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
	// And there we go, model matrix is ready!
}

void Model::Draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	// Ok, here I like to indent drawing calls - it's just a personal style, you may not like it and that's fine ;)
	// Generally you will need to be activating and deactivating OpenGL states
	// I just find it visually easier if the activations / deactivations happen at different tab depths
	// This can help when things get more complex

	// Activate the shader program
	glUseProgram(_program);

	// Activate the VAO
	glBindVertexArray(_VAO);

	// Send matrices to the shader as uniforms like this:
	glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_modelMatrix));
	glUniformMatrix4fv(_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(projMatrix));


	// Tell OpenGL to draw it
	// Must specify the type of geometry to draw and the number of vertices
	glDrawArrays(GL_TRIANGLES, 0, _numVertices);

	// Unbind VAO
	glBindVertexArray(0);

	// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
	glUseProgram(0);
}

