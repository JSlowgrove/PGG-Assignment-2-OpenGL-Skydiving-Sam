#include "Model.h"

#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>


// This does not belong here - should really have a nice shader class etc for sorting all this stuff out!
// Useful little function to just check for compiler errors
bool CheckShaderCompiled(GLint shader)
{
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete[] log;

		return false;
	}
	return true;
}








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
	// Creates one VAO
	glGenVertexArrays(1, &_VAO);
	// 'Binding' something makes it the current one we are using
	// This is like activating it, so that subsequent function calls will work on this item
	glBindVertexArray(_VAO);


	/*load the obj file*/
	std::vector<float> vertices;
	std::vector<float> vertexNormals;
	std::vector<float> vertexTextures;
	FileLoader::loadOBJFile("obj/train.obj", vertices, vertexNormals, vertexTextures);

	/*set the vertices array to the contents of the vector*/
	float* verticesArray = &vertices[0];
	/*set the number of vertices's*/
	_numVertices = vertices.size();

	// Variable for storing a VBO
	GLuint positionBuffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &positionBuffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices, verticesArray, GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	// (We will look at this properly in the lectures)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	/*set the normal array to the contents of the vector*/
	float* normals = &vertexNormals[0];

	// Variable for storing a VBO
	GLuint normalBuffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &normalBuffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices, normals, GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);






	// Unbind for neatness, it just makes life easier
	// As a general tip, especially as you're still learning, for each function that needs to do something specific try to return OpenGL in the state you found it in
	// This means you will need to set the states at the beginning of your function and set them back at the end
	// If you don't do this, your function could rely on states being set elsewhere and it's easy to lose track of this as your project grows
	// If you then change the code from elsewhere, your current code could mysteriously stop working properly!
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Technically we can do this, because the enabled / disabled state is stored in the VAO
	//glDisableVertexAttribArray(0);

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

