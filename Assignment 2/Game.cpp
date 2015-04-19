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

	/*a shared pointer variable to create the initial models*/
	std::shared_ptr<Model> model;
		
	/*Create a samurai model*/
	model.reset(new Model("default", "default", "samurai", objects, shaders));
	/*create a player entity using the model*/
	player = new Player(model, 0.15f);

	/*Create a ring model*/
	model.reset(new Model("default", "default", "ring", objects, shaders));
	/*create a targetRing entity using the model*/
	targetRing = new Ring(model, 0.15f);

	/*Create a shopping centre model*/
	model.reset(new Model("default", "default", "shoppingCentre", objects, shaders));
	/*create a ground entity using the model*/
	ground = new Ground(model, 0.05f);
	
	/*set the initial entity positions*/
	player->setPosition(0.0f, -0.4f, 0.0f);
	targetRing->setPosition(0.0f, 0.0f, -30.0f);
	ground->setPosition(-1.0f, 1.0f, -70.0f);

	/*set the initial entity rotations*/
	player->rotateY(Utilities::convertAngleToRadian(180.0f));
	targetRing->rotateX(Utilities::convertAngleToRadian(90.0f));
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
	delete targetRing;
	delete ground;
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

	/*Update the target ring*/
	targetRing->update(dt);
	
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

	/*Draw the target ring using the camera*/
	targetRing->draw(camera->getView(), camera->getProjection());

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