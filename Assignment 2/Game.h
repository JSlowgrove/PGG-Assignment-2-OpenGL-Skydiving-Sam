#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Utilities.h"
#include "State.h"
#include "StateManager.h"
#include "Camera.h"
#include "Entity.h"
#include "GameUI.h"
#include "LoadingScreen.h"

/**
@brief Creates an Game object that inherits State and runs the Game.
@author Jamie Slowgrove
*/
class Game : public State
{
private:
	/**The loaded Object files*/
	std::unordered_map<std::string, Object*> objects;
	/*The loaded Shader files*/
	std::unordered_map<std::string, Shader*> shaders;
	/**The Entities*/
	Entity *samurai;
	/**The Camera for the Game*/
	Camera *camera;
	/**The GameUI*/
	GameUI * userInterface;

	/**
	Draws a LoadingScreen.
	*/
	void loadingScreen();

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
	@param float The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};