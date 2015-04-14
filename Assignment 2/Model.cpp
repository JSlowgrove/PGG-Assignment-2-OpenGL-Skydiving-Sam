#include "Model.h"

/**************************************************************************************************************/

/*Constructs a Model Object.*/
Model::Model(std::string vertexShaderFileLocation, std::string fragmentShaderFileLocation, std::string objFileName)
{
	/*initialise the shader*/
	initialiseShaders(vertexShaderFileLocation, fragmentShaderFileLocation);
	/*initialise the object*/
	initialiseVAO(objFileName);
}

/**************************************************************************************************************/

/*Destructs a Model Object.*/
Model::~Model()
{
}

/**************************************************************************************************************/

/*Initialise the object for the Model.*/
void Model::initialiseVAO(std::string objFileName)
{
	/*initialise the object*/
	obj = new Object(objFileName);
}

/**************************************************************************************************************/

/*Initialise the shaders.*/
void Model::initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
	/*initialise the shader*/
	shader = new Shader(vertexShaderFileName, fragmentShaderFileName);
}

/**************************************************************************************************************/

/*Draw the Model to the screen.*/
void Model::draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	/*Activate the shader program*/
	glUseProgram(shader->getShaderProgram());

	/*Activate the vertex array object*/
	glBindVertexArray(obj->getVBO());

	/*Send the matrices to the shader as uniforms loactions*/
	glUniformMatrix4fv(shader->getModelMatrixLocation(), 1, GL_FALSE, glm::value_ptr(matrix));
	glUniformMatrix4fv(shader->getViewMatrixLocation(), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader->getShaderProjectionMatrixLocation(), 1, GL_FALSE, glm::value_ptr(projMatrix));

	/*Draw the model to the screen, using the type of geometry and the number of vertices*/
	glDrawArrays(GL_TRIANGLES, 0, obj->getNumberOfVertices());

	/*Unbind the vertex array object*/
	glBindVertexArray(0);

	/*disable the shader program*/
	glUseProgram(0);
}

/**************************************************************************************************************/

/*Sets the position of the Model.*/
void Model::setPosition(glm::vec3 position)
{
	/*set the position*/
	this->position = position;
	/*move the model to the new position*/
	matrix = glm::translate(glm::mat4(1.0f), position);
}

/**************************************************************************************************************/

/*Sets the position of the Model.*/
void Model::setPosition(float x, float y, float z)
{ 
	/*set the x position*/
	position.x = x; 
	/*set the y position*/
	position.y = y; 
	/*set the z position*/
	position.z = z; 
	/*move the model to the new position*/
	matrix = glm::translate(glm::mat4(1.0f), position);
}

/**************************************************************************************************************/

/*Rotate the Model along the X axis.*/
void Model::rotateX(float angle)
{
	/*rotate the model*/
	matrix = glm::rotate(matrix, angle, glm::vec3(1, 0, 0));
}

/**************************************************************************************************************/

/*Rotate the Model along the Y axis.*/
void Model::rotateY(float angle)
{
	/*rotate the model*/
	matrix = glm::rotate(matrix, angle, glm::vec3(0, 1, 0));
}

/**************************************************************************************************************/

/*Rotate the Model along the Z axis.*/
void Model::rotateZ(float angle)
{
	/*rotate the model*/
	matrix = glm::rotate(matrix, angle, glm::vec3(0, 0, 1));
}

/**************************************************************************************************************/

/*Scale the Model.*/
void Model::scale(glm::vec3 scaleVector)
{
	/*scale the model*/
	matrix = glm::scale(matrix, scaleVector);
}