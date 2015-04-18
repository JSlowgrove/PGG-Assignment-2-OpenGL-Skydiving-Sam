#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Utilities.h"
#include "State.h"
#include "StateManager.h"
#include "Audio.h"
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
	/**The background music*/
	Audio * music;
	/**The Entities*/
	Entity *samurai;
	Entity *targetRing;
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
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	*/
	Game(StateManager* stateManager, SDL_Window* window, int screenWidth, int screenHeight);

	/**
	Destructs an Game object.
	*/
	~Game();

	/**
	Handles the Game input.
	@returns If false then quit the Game State.
	*/
	bool input();

	/**
	A function to update the Game.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};