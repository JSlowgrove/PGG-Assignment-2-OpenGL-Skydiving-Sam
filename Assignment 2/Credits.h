#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Utilities.h"
#include "State.h"
#include "StateManager.h"
#include "Camera.h"
#include "Audio.h"
#include "CreditsUI.h"
#include "Object.h"
#include "Shader.h"

/**
@brief Creates an Credits object that inherits State and runs the Help screen.
@author Jamie Slowgrove
*/
class Credits : public State
{
private:
	/**The loaded Object files*/
	std::unordered_map<std::string, Object*> objects;
	/**The loaded Shader files*/
	std::unordered_map<std::string, Shader*> shaders;
	/**The Camera for the Credits*/
	Camera *camera;
	/**The CreditsUI*/
	CreditsUI * userInterface;
	/**The background music*/
	Audio* music;

	/**
	Draws a LoadingScreen.
	*/
	void loadingScreen();

public:
	/**
	Constructs a Credits object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	@param music A pointer to the background music.
	*/
	Credits(StateManager* stateManager, SDL_Window* window, int screenWidth, int screenHeight, Audio* music);

	/**
	Destructs an Credits object.
	*/
	~Credits();

	/**
	Handles the Credits input.
	@returns If false then quit the Credits State.
	*/
	bool input();

	/**
	A function to update the Credits.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};