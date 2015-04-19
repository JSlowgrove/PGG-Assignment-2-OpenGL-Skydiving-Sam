#include "Game.h"
#include "MainMenu.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*draw a loading screen*/
	loadingScreen();

	/*Initialise the Camera*/
	camera = new Camera();

	/*initialize random seed: */
	srand((unsigned int)time(NULL));

	/*create a player entity using a samurai model*/
	player = new Player(new Model("default", "default", "samurai", objects, shaders), 0.15f);

	/*loop for the number of ring targets*/
	for (int i = 0; i < NUM_OF_TARGETS; i++)
	{
		/*get a random scale between 0.08 and 0.25*/
		float scaleValue = (float)((rand() % 18) + 8) * 0.01f;
		/*push a new Ring entity using a ring model to the targetRings vector*/
		targetRings.push_back(new Ring(new Model("default", "default", "ring", objects, shaders), scaleValue));
	}

	/*create a ground entity using a shopping centre model*/
	ground = new Ground(new Model("default", "default", "shoppingCentre", objects, shaders), 0.05f);
	
	/*set the initial entity positions*/
	player->setPosition(0.0f, -0.4f, 0.0f);
	/*loop for the number of ring targets*/
	for (int i = 0; i < NUM_OF_TARGETS; i++)
	{
		/*get a random x position between -1.5 and 1.5*/
		float x = (float)((rand() % 30) - 15) * 0.1f;
		/*get a random y position between -1.5 and 1.5*/
		float y = (float)((rand() % 30) - 15) * 0.1f;
		/*work out the z position*/
		float z = -20.0f - (i * 5.0f);
		/*initialise the position*/
		targetRings[i]->setPosition(x, y, z);
	}
	/*work out the z position for the ground*/
	float z = -20.0f - (NUM_OF_TARGETS * 5.0f);
	ground->setPosition(-1.0f, 1.0f, z);

	/*set the initial entity rotations*/
	player->rotateY(Utilities::convertAngleToRadian(180.0f));
	/*loop through all the ring targets*/
	for (auto targetRing : targetRings)
	{
		targetRing->rotateX(Utilities::convertAngleToRadian(90.0f));
	}
	ground->rotateX(Utilities::convertAngleToRadian(90.0f));

	/*initialise the UI*/
	userInterface = new GameUI("2d.default", "2d.default", shaders);

	/*stop the loading music*/
	music->stopAudio();

	/*initialise and start the music*/
	music = new Audio("aud/Harmful or Fatal.ogg", true);
	music->startAudio();
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	/*stop music*/
	music->stopAudio();
	/*delete audio pointers*/
	delete music;
	/*delete pointers*/
	delete camera;
	delete player;
	delete ground;
	for (auto targetRing : targetRings)
	{
		delete targetRing;
	}
	for (auto i = objects.begin(); i != objects.end(); ++i)
	{
		delete i->second;
	}
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
bool Game::input()
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
			case SDLK_ESCAPE: /*If escape is pressed, go back to the main menu*/

				/*stop music*/
				music->stopAudio();
				/*go to the game state*/
				stateManager->changeState(new MainMenu(stateManager, window, screenWidth, screenHeight));
				return true;
				break;
			}
		}
		/*handle the player inputs*/
		player->input(incomingEvent);
	}
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void Game::update(float dt)
{
	/*keep the music playing*/
	music->startAudio();

	/*Update the player*/
	player->update(dt);

	/*loop through all of the target rings*/
	for (auto targetRing : targetRings)
	{
		/*update the target ring speed*/
		targetRing->setMoveSpeed(player->getWorldSpeed());
		/*Update the target ring*/
		targetRing->update(dt);
	}
	
	/*update the ground speed*/
	ground->setMoveSpeed(player->getWorldSpeed());
	/*Update the ground*/
	ground->update(dt);
}

/**************************************************************************************************************/

/*draws the game*/
void Game::draw()
{
	/*clear the frame-buffer to a colour*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/*write colour to the frame-buffer*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*Draw the player using the camera*/
	player->draw(camera->getView(), camera->getProjection());

	/*loop through all of the target rings*/
	for (auto targetRing : targetRings)
	{
		/*Draw the target ring using the camera*/
		targetRing->draw(camera->getView(), camera->getProjection());
	}

	/*Draw the ground using the camera*/
	ground->draw(camera->getView(), camera->getProjection());

	/*draw the UI*/
	userInterface->draw();
	
	/*display the window*/
	SDL_GL_SwapWindow(window);
}

/**************************************************************************************************************/

/*Draws a LoadingScreen.*/
void Game::loadingScreen()
{
	/*initialise and start the loading music*/
	music = new Audio("aud/Cut Trance.ogg", true);
	music->startAudio();

	/*create the loading screen*/
	LoadingScreen * loadingScreen = new LoadingScreen("2d.default", "2d.default", shaders);

	/*clear the frame-buffer to a colour*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/*write colour to the frame-buffer*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*draw the loading screen*/
	loadingScreen->draw();

	/*display the window*/
	SDL_GL_SwapWindow(window);

	/*delete the loading screen*/
	delete loadingScreen;
}