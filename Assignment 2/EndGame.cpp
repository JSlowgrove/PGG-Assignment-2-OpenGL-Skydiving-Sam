#include "EndGame.h"
#include "MainMenu.h"

/**************************************************************************************************************/

/*Constructs the EndGame object*/
EndGame::EndGame(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight,
	Audio* music, float score) : State(stateManager, window, screenWidth, screenHeight)
{
	/*Initialise the Camera*/
	camera = new Camera();

	/*store the music pointer*/
	this->music = music;

	/*initialise the menu UI*/
	userInterface = new EndGameUI("2d.default", "2d.default", shaders);
}

/**************************************************************************************************************/

/*Destructs the EndGame object*/
EndGame::~EndGame()
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
bool EndGame::input()
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
			case SDLK_ESCAPE: /*If enter is pressed the return to the Main Menu state*/

				/*stop music*/
				music->stopAudio();
				/*go to the main menu state*/
				stateManager->changeState(new MainMenu(stateManager, window, screenWidth, screenHeight));
				break;

			case SDLK_RETURN: /*If enter is pressed reset the game*/

				/*return to the game state*/
				stateManager->removeLastState();
				break;
			}
			break;
		}
	}
	return true;
}

/**************************************************************************************************************/

/*updates the EndGame screen*/
void EndGame::update(float dt)
{
	/*keep the music playing*/
	music->startAudio();
}

/**************************************************************************************************************/

/*draws the EndGame screen*/
void EndGame::draw()
{
	/*draw the UI*/
	userInterface->draw();
}