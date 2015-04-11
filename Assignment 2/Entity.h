#pragma once

#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "glew.h"
#include "Model.h"

/**
@brief Creates an Entity containing a Model.
*/
class Entity
{
private:
	/**A pointer to the Model*/
	Model* model;
	/**The rotation of the Entity Model (Euler angles)*/
	glm::vec3 rotation;
	/**The Position of the Model*/
	glm::vec3 position;

public:
	/**
	Constructs a Entity Object.
	Creates a Entity Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param std::string The location of the vertex shader file.
	@param std::string The location of the fragment shader file.
	@param std::string The location of the obj file.
	*/
	Entity(std::string vertexShaderFileLocation, std::string fragmentShaderFileLocation, std::string objFileLocation);

	/**
	Destructs a Entity Object.
	Destructs the Entity Object deleting the Entity Object from memory.
	*/
	~Entity();

	/**
	Updates the Entity
	@param float The delta time.
	*/
	void update(float deltaTs);

	/**
	Draw the Entity to the screen.
	@param glm::mat4 A reference to the camera view matrix.
	@param glm::mat4 A reference to the camera projection matrix.
	*/
	void draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	/**
	Setter # Sets the position of the Entity.
	@param glm::vec3 The new position.
	*/
	void setPosition(glm::vec3 position);

	/**
	Setter # Sets the position of the Entity.
	@param float The X position.
	@param float The Y position.
	@param float The Z position.
	*/
	void setPosition(float x, float y, float z);
};
