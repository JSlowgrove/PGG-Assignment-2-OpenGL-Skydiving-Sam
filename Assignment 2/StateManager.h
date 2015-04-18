#pragma once

#include <vector>
#include <iostream>
#include "State.h"

/**
@brief Creates a StateManager object.
Creates a StateManager object to be inherited.
DISCLAMER - This is my PGG Assignment 1 state manager class.
@author Jamie Slowgrove
*/
class StateManager
{
private:
	/**The current states that are in use*/
	std::vector<State*> currentStates;

public:
	/**
	Constructs a StateManager object.
	*/
	StateManager();

	/**
	Destructs a StateManager object.
	*/
	~StateManager();

	/**
	Adds a new state to the current stack of states.
	@param state A pointer to the State in use.
	*/
	void addState(State* state);

	/**
	Changes the current State to a new State.
	@param state A pointer to the State in use.
	*/
	void changeState(State* state);

	/**
	Removes the last State from the vector.
	*/
	void removeLastState();

	/**
	Handles the user input.
	The input function that will allow the equivalent input function to run in the current State.
	@returns If false then quit the application.
	*/
	bool input();

	/**
	Updates the current State.
	The update function that will allow the equivalent update function to run in the current State.
	@param dt The delta time for use within the update function.
	*/
	void update(float dt);

	/**
	Draws the current State.
	The draw function that will allow the equivalent draw function to run in the current State.
	*/
	void draw();
};