#include "Model.h"

/**************************************************************************************************************/

/*Constructs a Model Object.*/
Model::Model(std::string vertexShaderFileLocation, std::string fragmentShaderFileLocation, std::string objFileName,
	std::unordered_map<std::string, Object*> &objects, std::unordered_map<std::string, Shader*> &shaders)
{
	/*initialise the shader*/
	initialiseShaders(vertexShaderFileLocation, fragmentShaderFileLocation, shaders);
	/*initialise the object*/
	initialiseVAO(objFileName, objects);
}

/**************************************************************************************************************/

/*Destructs a Model Object.*/
Model::~Model()
{
}

/**************************************************************************************************************/

/*Initialise the object for the Model.*/
void Model::initialiseVAO(std::string objFileName, std::unordered_map<std::string, Object*> &objects)
{
	/*test if the object has already been loaded*/
	if (objects.count(objFileName) == 0)
	{
		/*load the object*/
		objects[objFileName] = new Object(objFileName);
	}
	else
	{
		/*print out that it is already loaded*/
		std::cout << objFileName << " object already loaded." << std::endl << std::endl;
	}
	/*initialise the object*/
	obj = objects[objFileName];
}

/**************************************************************************************************************/

/*Initialise the shaders.*/
void Model::initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
{
	/*a string for the name of the linked shader*/
	std::string linkedShaderName = vertexShaderFileName + "/" + fragmentShaderFileName;

	/*test if the shader has already been loaded*/
	if(shaders.count(linkedShaderName) == 0)
	{
		/*load the shader*/
		shaders[linkedShaderName] = new Shader(vertexShaderFileName, fragmentShaderFileName);
	}
	else
	{
		/*print out that it is already loaded*/
		std::cout << linkedShaderName << " shader already loaded." << std::endl << std::endl;
	}
	/*initialise the object*/
	shader = shaders[linkedShaderName];
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
	matrix = glm::rotate(matrix, angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

/**************************************************************************************************************/

/*Rotate the Model along the Y axis.*/
void Model::rotateY(float angle)
{
	/*rotate the model*/
	matrix = glm::rotate(matrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

/**************************************************************************************************************/

/*Rotate the Model along the Z axis.*/
void Model::rotateZ(float angle)
{
	/*rotate the model*/
	matrix = glm::rotate(matrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

/**************************************************************************************************************/

/*Scale the Model.*/
void Model::scale(glm::vec3 scaleVector)
{
	/*scale the model*/
	matrix = glm::scale(matrix, scaleVector);
}