#include "Game.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*Initialise the Camera*/
	camera = new Camera();
		
	// Create a samurai model
	std::shared_ptr<Model> model;
	model.reset(new Model("default", "default", "samurai", objects, shaders));
	samurai = new Entity(model, 0.1f);


	// Set object's position like this:
	samurai->setPosition(0.0f, 0.0f, 0.0f);

	/*initialise the UI*/
	userInterface = new UI("2d.default", "2d.default", shaders);
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
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
		
		/*update the camera input*/
		camera->input(incomingEvent);
	}
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void Game::update(float dt)
{
	// Update the model, to make it rotate
	samurai->update(dt);

	/*update the camera*/
	camera->update(dt);
}

/**************************************************************************************************************/

/*draws the game*/
void Game::draw()
{
	/*clear the frame-buffer to a colour*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/*write colour to the frame-buffer*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*Draw the object using the camera*/
	samurai->draw(camera->getView(), camera->getProjection());

	/*draw the UI*/
	userInterface->draw();
	
	/*display the window*/
	SDL_GL_SwapWindow(window);
}