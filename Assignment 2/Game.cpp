#include "Game.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*draw a loading screen*/
	loadingScreen();

	/*Initialise the Camera*/
	camera = new Camera();

	/*a shared pointer variable to create the initial models*/
	std::shared_ptr<Model> model;
		
	/*Create a samurai model*/
	model.reset(new Model("default", "default", "samurai", objects, shaders));
	/*create a samurai entity using the model*/
	samurai = new Entity(model, 0.15f);

	/*Create a ring model*/
	model.reset(new Model("default", "default", "ring", objects, shaders));
	/*create a targetRing entity using the model*/
	targetRing = new Entity(model, 0.15f);
	
	/*set the initial entity positions*/
	samurai->setPosition(0.0f, -0.4f, 0.0f);
	targetRing->setPosition(0.0f, 0.0f, 0.0f);

	/*set the initial entity rotations*/
	samurai->rotateY(Utilities::convertAngleToRadian(180.0f));
	targetRing->rotateX(Utilities::convertAngleToRadian(90.0f));

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
	delete samurai;
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
			case SDLK_ESCAPE: /*If escape is pressed, end the game loop*/

				return false;
				break;
			}
		}
	}
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void Game::update(float dt)
{
	/*keep the music playing*/
	music->startAudio();

	/*Update the samurai*/
	samurai->update(dt);

	/*Update the target ring*/
	targetRing->update(dt);
}

/**************************************************************************************************************/

/*draws the game*/
void Game::draw()
{
	/*clear the frame-buffer to a colour*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/*write colour to the frame-buffer*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*Draw the samurai using the camera*/
	samurai->draw(camera->getView(), camera->getProjection());

	/*Draw the target ring using the camera*/
	targetRing->draw(camera->getView(), camera->getProjection());

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