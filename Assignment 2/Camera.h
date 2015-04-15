#pragma once

#include <SDL.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "glew.h"

/**
@brief Creates an Camera object.
@author Jamie Slowgrove
*/
class Camera
{
private:
	/*Create a viewing matrix for the Camera (Camera orientation)*/
	glm::mat4 view;
	/*Construct a projection matrix for the Camera (Camera lense)*/
	glm::mat4 projection;
	/*The Orientation of the Camera*/
	glm::vec3 orientation;
	/**The movement speed of the Camera*/
	float moveSpeed;
	/**The rotation speed of the Camera*/
	float rotateSpeed;
	/**Camera movement*/
	bool up, down, left, right, forwards, backwards, rotateRight,
		rotateLeft, rotateUp, rotateDown, rollLeft, rollRight;
	/**Current Mouse position*/
	glm::vec2 mouse;

public:
	/**
	Constructs a Camera object.
	*/
	Camera();

	/**
	Destructs an Camera object.
	*/
	~Camera();

	/**
	Handles inputs for the Camera.
	@param SDL_Event A reference to the input event.
	*/
	void input(SDL_Event &incomingEvent);

	/**
	A function to update the Camera.
	@param float The delta time.
	*/
	void update(float dt);

	/**
	Moves the Camera using the translation.
	@param glm::vec3 The translation.
	*/
	void moveCamera(glm::vec3 translation);

	/**
	Moves the Camera along the X axis.
	@param float The translation along the X axis.
	*/
	void moveCameraAlongX(float translateX);

	/**
	Moves the Camera along the Y axis.
	@param float The translation along the Y axis.
	*/
	void moveCameraAlongY(float translateY);

	/**
	Moves the Camera along the Z axis.
	@param float The translation along the Z axis.
	*/
	void moveCameraAlongZ(float translateZ);

	/**
	Rotates the Camera using the rotation.
	@param glm::vec3 The rotation.
	*/
	void rotateCamera(glm::vec3 rotation);

	/**
	Rotate the Camera along the X axis.
	@param float The rotation along the X axis.
	*/
	void rotateCameraAlongX(float rotationX);

	/**
	Rotate the Camera along the Y axis.
	@param float The rotation along the Y axis.
	*/
	void rotateCameraAlongY(float rotationY);

	/**
	Rotate the Camera along the Z axis.
	@param float The rotation along the Z axis.
	*/
	void rotateCameraAlongZ(float rotationZ);

	/**
	Getter # Returns the Camera view matrix.
	@returns glm::mat4 The Camera view matrix.
	*/
	glm::mat4 getView();

	/**
	Getter # Returns the Camera projection matrix.
	@returns glm::mat4 The Camera projection matrix.
	*/
	glm::mat4 getProjection();

	/**
	Getter # Returns the Camera orientation.
	@returns glm::vec3 The Camera orientation.
	*/
	glm::vec3 getOrientation();
};