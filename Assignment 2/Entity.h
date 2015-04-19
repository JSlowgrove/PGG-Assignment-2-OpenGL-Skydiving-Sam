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
	/**The movement speed of the Entity*/
	float moveSpeed;
	/**The rotation speed of the Entity*/
	float rotateSpeed;

public:
	/**
	Constructs a Entity Object.
	Creates a Entity Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param model A shared pointer to the model.
	@param scaleValue The scale of the Model.
	*/
	Entity(std::shared_ptr<Model> model, float scaleValue);

	/**
	A virtual destructor for the Entity Object.
	Destructs the Entity Object deleting the Entity Object from memory.
	*/
	virtual ~Entity();

	/**
	A pure virtual function that updates the Entity
	@param dt The delta time.
	*/
	virtual void update(float dt) = 0;

	/**
	Draw the Entity to the screen.
	@param viewMatrix A reference to the camera view matrix.
	@param projMatrix A reference to the camera projection matrix.
	*/
	void draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	/**
	Setter # Sets the position of the Entity.
	@param position The new position.
	*/
	void setPosition(glm::vec3 position);

	/**
	Setter # Sets the position of the Entity.
	@param x The X position.
	@param y The Y position.
	@param z The Z position.
	*/
	void setPosition(float x, float y, float z);

	/**
	Rotate the Entity along the X axis.
	@param angle The rotation angle (Euler angle [Radians]).
	*/
	void rotateX(float angle);

	/**
	Rotate the Entity along the Y axis.
	@param angle The rotation angle (Euler angle [Radians]).
	*/
	void rotateY(float angle);

	/**
	Rotate the Entity along the Z axis.
	@param angle The rotation angle (Euler angle [Radians]).
	*/
	void rotateZ(float angle);

	/**
	Setter # Sets the scale of the Entity.
	@param scaleValue The new scale.
	*/
	void setScale(float scaleValue);

	/**
	Move the Entity.
	@param movement The amount to move by.
	*/
	void move(glm::vec3 movement);

	/**
	Move the Entity along the X axis.
	@param movement The amount to move by.
	*/
	void moveX(float movement);

	/**
	Move the Entity along the Y axis.
	@param movement The amount to move by.
	*/
	void moveY(float movement);

	/**
	Move the Entity along the Z axis.
	@param movement The amount to move by.
	*/
	void moveZ(float movement);

	/**
	Getter # Gets the position of the Entity.
	@returns The position of the Entity.
	*/
	glm::vec3 getPosition();

	/**
	Getter # Gets the position of the Entity.
	@returns The orientation of the Entity.
	*/
	glm::vec3 getOrientation();
};
