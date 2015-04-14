#pragma once

#include <SDL.h>
#include <iostream>
#include <string.h>

/**Forward declaration of StateManager for the pointer to the StateManager*/
class StateManager;

/**
@brief Creates a State object.
Creates a State object to be inherited.
DISCLAMER - This is a modified version of my PGG Assignment 1 state class.
@author Jamie Slowgrove
*/
class State
{
protected:
	/**A pointer to the state manager*/
	StateManager* stateManager;
	/**The window to display to*/
	SDL_Window* window;
	/**The width of the screen*/
	int screenWidth;
	/**The height of the screen*/
	int screenHeight;

public:
	/**
	Constructs a State object.
	@param StateManager * A pointer to the StateManager.
	@param SDL_Window * A pointer to the window in use.
	@param int The screen width.
	@param int The screen height.
	*/
	State(StateManager* stateManager, SDL_Window* window, int screenWidth, int screenHeight);

	/**
	A virtual destructor for the State object.
	*/
	virtual ~State();

	/**
	A pure virtual function to handle the user input.
	A pure virtual function to handle the user input for use with the State.
	@returns bool If false then quit State.
	*/
	virtual bool input() = 0;

	/**
	A pure virtual function to update the State.
	A pure virtual function to update the State to allow the State to run.
	@param float The delta time.
	*/
	virtual void update(float deltaTime) = 0;

	/**
	A pure virtual function to draw to the screen.
	A pure virtual function to draw to the screen using the renderer.
	*/
	virtual void draw() = 0;
};