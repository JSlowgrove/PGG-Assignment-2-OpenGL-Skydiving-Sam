#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Utilities.h"
#include "State.h"
#include "StateManager.h"
#include "Camera.h"
#include "HelpUI.h"
#include "Object.h"
#include "Shader.h"

/**
@brief Creates an Help object that inherits State and runs the Help screen.
@author Jamie Slowgrove
*/
class Help : public State
{
private:
	/**The loaded Object files*/
	std::unordered_map<std::string, Object*> objects;
	/**The loaded Shader files*/
	std::unordered_map<std::string, Shader*> shaders;
	/**The Camera for the Help*/
	Camera *camera;
	/**The MainMenuUI*/
	HelpUI * userInterface;

	/**
	Draws a LoadingScreen.
	*/
	void loadingScreen();

public:
	/**
	Constructs a Help object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	*/
	Help(StateManager* stateManager, SDL_Window* window, int screenWidth, int screenHeight);

	/**
	Destructs an Help object.
	*/
	~Help();

	/**
	Handles the Help input.
	@returns If false then quit the Help State.
	*/
	bool input();

	/**
	A function to update the Help.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};