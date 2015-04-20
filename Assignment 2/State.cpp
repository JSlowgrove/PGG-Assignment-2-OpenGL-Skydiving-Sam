#include "State.h"

/**************************************************************************************************************/

/*Constructs the state object*/
State::State(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
{
	/*sets the pointer to the state manager*/
	this->stateManager = stateManager;
	/*sets the pointer to the window*/
	this->window = window;
	/*load the screen dimensions*/
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

}

/**************************************************************************************************************/

/*Destructs the state object*/
State::~State() 
{
}


/**************************************************************************************************************/

/*Returns the states window*/
SDL_Window* State::getWindow()
{
	/*return the window*/
	return window;
}