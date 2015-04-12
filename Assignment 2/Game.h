#pragma once

#include <SDL.h>
#include <iostream>
#include "State.h"
#include "StateManager.h"
#include "Camera.h"
#include "Entity.h"

/**
@brief Creates an Game object that inherits State and runs the Game.
*/
class Game : public State
{
private:
	/**The Entities*/
	Entity *train;
	Entity *myObject;
	/**The Camera for the Game*/
	Camera *camera;
	/**Camera movement*/
	bool up, down, left, right, forwards, backwards;
public:
	/**
	Constructs a Game object.
	@param StateManager * A pointer to the StateManager.
	@param SDL_Window * A pointer to the window.
	@param int The screen width.
	@param int The screen height.
	*/
	Game(StateManager* stateManager, SDL_Window* window, int screenWidth, int screenHeight);

	/**
	Destructs an Game object.
	*/
	~Game();

	/**
	Handles the Game input.
	@returns bool If false then quit the Game State.
	*/
	bool input();

	/**
	A function to update the Game.
	A function to update the Game to allow the Game to run.
	@param float The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};