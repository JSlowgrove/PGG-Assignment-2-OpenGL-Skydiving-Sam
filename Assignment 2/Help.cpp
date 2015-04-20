#include "Help.h"

/**************************************************************************************************************/

/*Constructs the Help object*/
Help::Help(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*Initialise the Camera*/
	camera = new Camera();
	
	/*initialise the menu UI*/
	userInterface = new HelpUI("2d.default", "2d.default", shaders);
}

/**************************************************************************************************************/

/*Destructs the Help object*/
Help::~Help()
{
	/*delete pointers*/
	delete camera;
	for (auto i = objects.begin(); i != objects.end(); ++i)
	{
		delete i->second;
	}
	for (auto i = shaders.begin(); i != shaders.end(); ++i)
	{
		delete i->second;
	}
	delete userInterface;
}

/**************************************************************************************************************/

/*handles inputs*/
bool Help::input()
{
	/*Check for user input*/
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT: /*If player closes the window, end the game loop*/

			return false;
			break;

		case SDL_KEYDOWN:

			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_RETURN: /*If enter is pressed the game return to the game state*/

				/*go to the game state*/
				stateManager->removeLastState();
				break;
			}
			break;
		}
	}
	return true;
}

/**************************************************************************************************************/

/*updates the help screen*/
void Help::update(float dt)
{
}

/**************************************************************************************************************/

/*draws the help screen*/
void Help::draw()
{
	/*draw the UI*/
	userInterface->draw();
}