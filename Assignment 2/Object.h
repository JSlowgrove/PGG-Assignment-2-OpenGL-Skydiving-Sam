#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <glm.hpp>
#include <string>
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
	/**The name of the material*/
	std::string material;
	/**The Texture*/
	GLuint textureID;
	
	/**
	Initialise the texture.
	@param vertexTextures The vertex textures vector.
	*/
	void initialiseTexture(std::vector<float> vertexTextures);

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
	Constructs an Object.
	Creates a vertex array object using a obj file location and OpenGL.
	@param objFileName The name of the obj file.
	@param material The name of the material file.
	*/
	Object(std::string objFileName, std::string material);

	/**
	Destructs an Object.
	Destructs the Object deleting the Object from memory.
	*/
	~Object();
	
	/**
	Getter # Returns the vertex array object.
	@returns The vertex array object.
	*/
	GLuint getVAO();

	/**
	Getter # Returns the Texture ID.
	@returns The texture ID.
	*/
	GLuint getTextureID();

	/**
	Getter # Returns the number of vertices.
	@returns The number of vertices.
	*/
	unsigned int getNumberOfVertices();

};