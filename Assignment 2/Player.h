#pragma once

#include <SDL.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <memory>
#include "glew.h"
#include "Utilities.h"
#include "Entity.h"

/**
@brief Creates a Player object that inherits Entity.
@author Jamie Slowgrove
*/
class Player : public Entity
{
private:
	/**Movement commands*/
	bool up, down, left, right, rotateUp, rotateDown;
	/**The min angle the Player can be*/
	float minAngle;
	/**The speed the world moves*/
	float worldSpeed;

public:
	/**
	Constructs a Player Object.
	Creates a Player Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param model A pointer to the model.
	@param scaleValue The scale of the Model.
	*/
	Player(Model* model, float scaleValue);

	/**
	Destructs a Player Object.
	Destructs the Player Object deleting the Player Object from memory.
	*/
	~Player();

	/**
	A function that updates the Player
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	Handles inputs for the Player.
	@param incomingEvent A reference to the input event.
	*/
	void input(SDL_Event &incomingEvent);

	/**
	Updates the player movement.
	@param dt The delta time.
	*/
	void updateMovement(float dt);

	/**
	Updates the player rotation.
	@param dt The delta time.
	*/
	void updateRotation(float dt);

	/**
	Updates the player rotation.
	@param dt The delta time.
	@param direction The direction to rotate the player (1 for up, -1 for down).
	*/
	void updateRotationCheck(float dt, float direction);

	/**
	Getter # Gets the world speed of the Entity.
	@returns The world speed of the Entity.
	*/
	float getWorldSpeed();
};
