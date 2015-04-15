#include "UIObject.h"

/**************************************************************************************************************/

/*Constructs the UIObject*/
UIObject::UIObject(float x, float y, float width, float height)
{
	/*initialise the variables*/
	position.x = x;
	position.y = y;
	dimensions.x = width;
	dimensions.y = height;

	/*initialise the object*/
	initialiseObject();
}

/**************************************************************************************************************/

/*Destructs the UIObject*/
UIObject::~UIObject()
{

}

/**************************************************************************************************************/

/*Initialise the UIobject.*/
void UIObject::initialiseObject()
{
	/*convert the coordinates to work with OpenGL*/
	dimensions *= 0.01f;
	position = convertToOpenGLCoordinate(position);

	/*get the max coordinates using the dimensions*/
	float maxX = position.x + dimensions.x;
	float maxY = position.y - dimensions.y;

	/*Create a VBO*/
	glGenVertexArrays(1, &obj);
	/*activate the VBO*/
	glBindVertexArray(obj);

	/*Vertices for a square from two triangles*/
	float vertices[] = 
	{
		/*triangle 1*/
		position.x, position.y,
		position.x, maxY,
		maxX,		maxY,

		/*triangle 2*/
		position.x, position.y,
		maxX,		position.y,
		maxX,		maxY,
	};

	/*Variable for storing a VBO*/
	GLuint buffer = 0;
	/*Create a generic 'buffer'*/
	glGenBuffers(1, &buffer);
	/*activate the buffer as a VBO*/
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	/*send the data to OpenGL (num of vertices will always be 12 as it is 2 triangles)*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);

	/*link the VBO to the shader*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	/*deactivate the VBO*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/**************************************************************************************************************/

/*Converts the coordinates to work with OpenGL.*/
glm::vec2 UIObject::convertToOpenGLCoordinate(glm::vec2 coordinates)
{
	/*convert to openGL coordinates*/
	coordinates *= 0.01f;
	coordinates.x = coordinates.x - 1;
	coordinates.y = coordinates.y - 1;

	/*flip the object along the y*/
	coordinates.y *= -1;

	/*return the new coordinates*/
	return coordinates;
}

/**************************************************************************************************************/

/*Draw the UIObject*/
void UIObject::draw(Shader * shader)
{
	/*Get the shader program*/
	glUseProgram(shader->getShaderProgram());

	/*activate the object*/
	glBindVertexArray(obj);
	
	/*draw the object, the num of vertices will always be 6 as it is drawing 2 triangles for a rectangle*/
	glDrawArrays(GL_TRIANGLES, 0, 6);

	/*deactivate the object*/
	glBindVertexArray(0);

	/*deactivate the shader*/
	glUseProgram(0);
}
