#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Utilities.h"
#include "State.h"
#include "StateManager.h"
#include "Camera.h"
#include "Audio.h"
#include "EndGameUI.h"
#include "Object.h"
#include "Shader.h"

/**
@brief Creates an EndGame object that inherits State and runs the EndGame screen.
@author Jamie Slowgrove
*/
class EndGame : public State
{
private:
	/**The loaded Object files*/
	std::unordered_map<std::string, Object*> objects;
	/**The loaded Shader files*/
	std::unordered_map<std::string, Shader*> shaders;
	/**The Camera for the Help*/
	Camera *camera;
	/**The EndGameUI*/
	EndGameUI * userInterface;
	/**The background music*/
	Audio* music;

	/**
	Draws a LoadingScreen.
	*/
	void loadingScreen();

public:
	/**
	Constructs a EndGame object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	@param music A pointer to the background music.
	@param score The score from the Game.
	*/
	EndGame(StateManager* stateManager, SDL_Window* window, int screenWidth, int screenHeight, Audio* music, float score);

	/**
	Destructs an EndGame object.
	*/
	~EndGame();

	/**
	Handles the EndGame input.
	@returns If false then quit the EndGame State.
	*/
	bool input();

	/**
	A function to update the EndGame.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};