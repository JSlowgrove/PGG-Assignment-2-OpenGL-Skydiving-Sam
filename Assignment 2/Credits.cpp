#include "Credits.h"

/**************************************************************************************************************/

/*Constructs the Credits object*/
Credits::Credits(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight, Audio* music)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*Initialise the Camera*/
	camera = new Camera();

	/*store the music pointer*/
	this->music = music;

	/*initialise the menu UI*/
	userInterface = new CreditsUI(shaders);
}

/**************************************************************************************************************/

/*Destructs the Credits object*/
Credits::~Credits()
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
bool Credits::input()
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
			case SDLK_ESCAPE: /*If escape is pressed return to the main menu state*/

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

/*updates the Credits screen*/
void Credits::update(float dt)
{
	/*keep the music playing*/
	music->startAudio();
}

/**************************************************************************************************************/

/*draws the Credits screen*/
void Credits::draw()
{
	/*draw the UI*/
	userInterface->draw();
}