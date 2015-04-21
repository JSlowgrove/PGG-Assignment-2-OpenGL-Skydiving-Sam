#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Utilities.h"
#include "State.h"
#include "StateManager.h"
#include "Audio.h"
#include "Camera.h"
#include "MenuEntity.h"
#include "MainMenuUI.h"
#include "LoadingScreen.h"

/**
@brief Creates an MainMenu object that inherits State and runs the MainMenu.
@author Jamie Slowgrove
DISCLAMER - This uses bits from my PGG assignment 1 menu class.
*/
class MainMenu : public State
{
private:
	/**The loaded Object files*/
	std::unordered_map<std::string, Object*> objects;
	/**The loaded Shader files*/
	std::unordered_map<std::string, Shader*> shaders;
	/**The background music*/
	Audio* music;
	/**The Entities*/
	MenuEntity* sam;
	/**The Camera for the MainMenu*/
	Camera* camera;
	/**The MainMenuUI*/
	MainMenuUI* userInterface;
	/**Current Mouse position*/
	glm::vec2 mouse;
	/**variables for if menu keys are highlighted, can be 0 or 1*/
	int playKey, credKey, exitKey;
	/**which key is pressed, 0 for none*/
	int pressed;

	/**
	Draws a LoadingScreen.
	*/
	void loadingScreen();

public:
	/**
	Constructs a MainMenu object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	*/
	MainMenu(StateManager* stateManager, SDL_Window* window, int screenWidth, int screenHeight);

	/**
	Destructs an MainMenu object.
	*/
	~MainMenu();

	/**
	Handles the MainMenu input.
	@returns If false then quit the MainMenu State.
	*/
	bool input();

	/**
	A function to update the MainMenu.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};