#pragma once

#include <iostream>
#include <glm.hpp>
#include "glew.h"
#include "FileLoader.h"

/**
@brief Creates an object for use with OpenGL.
Creates an object from an text file, this can then be used with OpenGL.
@author Jamie Slowgrove
*/
class Object
{
private:
	/**The Vertex Array Object for use with OpenGL*/
	GLuint vertexArrayObject;
	/**Number of vertices in the model*/
	unsigned int numberOfVertices;

	/**
	Initialise the vertex array object.
	@param objFileName The name of the obj file.
	*/
	void InitialiseVAO(std::string objFileName);

public:
	/**
	Constructs an Object.
	Creates a vertex array object using a obj file location and OpenGL.
	@param objFileName The name of the obj file.
	*/
	Object(std::string objFileName);

	/**
	Destructs an Object.
	Destructs the Object deleting the Object from memory.
	*/
	~Object();
	
	/**
	Getter # Returns the vertex buffer object.
	@returns The vertex buffer object.
	*/
	GLuint getVBO();

	/**
	Getter # Returns the number of vertices.
	@returns The number of vertices.
	*/
	unsigned int getNumberOfVertices();

};