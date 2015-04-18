#pragma once

#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <memory>
#include "glew.h"
#include "Utilities.h"
#include "Model.h"

/**
@brief Creates an Entity containing a Model.
@author Jamie Slowgrove
*/
class Entity
{
protected:
	/**A pointer to the Model*/
	std::shared_ptr<Model> model;
	/**The rotation of the Entity Model (Euler angles)*/
	glm::vec3 rotation;
	/**The Position of the Model*/
	glm::vec3 position;
	/**The scale of the Model*/
	float scaleValue;

public:
	/**
	Constructs a Entity Object.
	Creates a Entity Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param Model A shared pointer to the model.
	@param float The scale of the Model.
	*/
	Entity(std::shared_ptr<Model> model, float scaleValue);

	/**
	Destructs a Entity Object.
	Destructs the Entity Object deleting the Entity Object from memory.
	*/
	~Entity();

	/**
	A virtual function that updates the Entity
	@param float The delta time.
	*/
	virtual void update(float deltaTs);

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

	/**
	Rotate the Entity along the X axis.
	@param float The rotation angle (Euler angle [Radians]).
	*/
	void rotateX(float angle);

	/**
	Rotate the Entity along the Y axis.
	@param float The rotation angle (Euler angle [Radians]).
	*/
	void rotateY(float angle);

	/**
	Rotate the Entity along the Z axis.
	@param float The rotation angle (Euler angle [Radians]).
	*/
	void rotateZ(float angle);

	/**
	Setter # Sets the scale of the Entity.
	@param float The new scale.
	*/
	void setScale(float scaleValue);
};
