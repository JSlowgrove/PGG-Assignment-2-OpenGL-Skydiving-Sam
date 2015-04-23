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

	/*initialise the texture bool*/
	textureBool = false;
	
	/*initialise the object*/
	initialiseObject();
}

/**************************************************************************************************************/

/*Constructs the UIObject*/
UIObject::UIObject(float x, float y, float width, float height, SDL_Surface* surface)
{
	/*initialise the variables*/
	position.x = x;
	position.y = y;
	dimensions.x = width;
	dimensions.y = height;
	
	/*initialise the texture bool*/
	textureBool = true;

	/*initialise the object*/
	initialiseObject(surface);
}

/**************************************************************************************************************/

/*Destructs the UIObject*/
UIObject::~UIObject()
{
	/*delete data*/
	glDeleteVertexArrays(1, &obj);
	glDeleteTextures(1, &textureID);
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

	/*delete the VBO*/
	glDeleteBuffers(1, &buffer);
}


/**************************************************************************************************************/

/*Initialise the UIobject.*/
void UIObject::initialiseObject(SDL_Surface* surface)
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
		maxX, maxY,

		/*triangle 2*/
		position.x, position.y,
		maxX, position.y,
		maxX, maxY,
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

	/*initialise the UI texture*/
	initialiseTexture(surface);

	/*deactivate the VBO*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*delete the VBO*/
	glDeleteBuffers(1, &buffer);

	/*disable the array*/
	glDisableVertexAttribArray(0);
}

/**************************************************************************************************************/

/*Initialise the texture.*/
void UIObject::initialiseTexture(SDL_Surface* surface)
{
	/*check and store the file format*/
	GLenum format;
	if (surface->format->BytesPerPixel == 3)
	{
		format = GL_RGB;
	}
	else if (surface->format->BytesPerPixel == 4)
	{
		format = GL_RGBA;
	}

	// texture coordinates
	float textureCoordinates[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	// Create one OpenGL texture
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Variable for storing a VBO
	GLuint textureBuffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &textureBuffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, textureCoordinates, GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	/*deactivate the VBO*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*delete the VBO*/
	glDeleteBuffers(1, &textureBuffer);
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

	/*turn on blending*/
	glEnable(GL_BLEND);

	/*turn on transparency (ALPHA * incomming   +  (1 - ALPHA) * current)*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*if the model uses a shader*/
	if (textureBool)
	{
		/*texturing*/
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glUniform1i(shader->getTextureSamplerLocation(), 0);
	}
	
	/*draw the object, the num of vertices will always be 6 as it is drawing 2 triangles for a rectangle*/
	glDrawArrays(GL_TRIANGLES, 0, 6);

	/*turn of blending*/
	glDisable(GL_BLEND);

	/*deactivate the object*/
	glBindVertexArray(0);

	/*deactivate the shader*/
	glUseProgram(0);
}
