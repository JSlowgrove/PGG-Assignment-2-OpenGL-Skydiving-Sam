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
public:
	/**
	Constructs a Player Object.
	Creates a Player Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param model A shared pointer to the model.
	@param scaleValue The scale of the Model.
	*/
	Player(std::shared_ptr<Model> model, float scaleValue);

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
};
