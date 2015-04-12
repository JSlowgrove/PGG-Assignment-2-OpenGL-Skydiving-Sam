#include "Game.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*Initalise the Camera*/
	camera = new Camera();
	// Create a model
	myObject = new Entity("shaders/vertexShader.txt", "shaders/fragmentShader.txt", "obj/train.obj");
	// Set object's position like this:
	myObject->setPosition(0, 0, 0);
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	
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
			case SDLK_ESCAPE: /*If Escape is pressed, end the game loop*/

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
	// Update the model, to make it rotate
	myObject->update(dt);
}

/**************************************************************************************************************/

/*draws the game*/
void Game::draw()
{
	// Draw our world

	// Specify the colour to clear the framebuffer to
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// This writes the above colour to the colour part of the framebuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*Draw the object using the camera*/
	myObject->draw(camera->getView(), camera->getProjection());

	// This tells the renderer to actually show its contents to the screen
	// We'll get into this sort of thing at a later date - or just look up 'double buffering' if you're impatient :P
	SDL_GL_SwapWindow(window);
}