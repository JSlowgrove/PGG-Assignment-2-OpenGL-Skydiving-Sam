#include "Game.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*Initialise the Camera*/
	camera = new Camera();
	// Create a model
	train = new Entity("shaders/vertexShader.txt", "shaders/fragmentShader.txt", "obj/train.obj", 0.2f);
	myObject = new Entity("shaders/vertexShader.txt", "shaders/fragmentShader.txt", "obj/cube.obj", 0.2f);
	// Set object's position like this:
	train->setPosition(0, 0, 0);
	myObject->setPosition(0, -0.5, 0);
	/*initialise the camera movement*/
	up = down = left = right = forwards = backwards = false;
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	/*delete pointers*/
	delete myObject;
	delete camera;
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

			case SDLK_q: /*If q is pressed, up is true*/
				up = true;
				break;

			case SDLK_e: /*If e is pressed, down is true*/
				down = true;
				break;

			case SDLK_w: /*If w is pressed, forwards is true*/				
				forwards = true;
				break;

			case SDLK_s: /*If s is pressed, backwards is true*/
				backwards = true;
				break;

			case SDLK_a: /*If a is pressed, left is true*/
				left = true;
				break;

			case SDLK_d: /*If s is pressed, right is true*/
				right = true;
				break;
			}
			break;

		case SDL_KEYUP:

			switch (incomingEvent.key.keysym.sym)
			{

			case SDLK_q: /*If q is pressed, up is false*/
				up = false;
				break;

			case SDLK_e: /*If e is pressed, down is false*/
				down = false;
				break;

			case SDLK_w: /*If w is pressed, forwards is false*/
				forwards = false;
				break;

			case SDLK_s: /*If s is pressed, backwards is false*/
				backwards = false;
				break;

			case SDLK_a: /*If a is pressed, left is false*/
				left = false;
				break;

			case SDLK_d: /*If s is pressed, right is false*/
				right = false;
				break;
			}
			break;
		}
	}
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void Game::update(float dt)
{
	// Update the model, to make it rotate
	train->update(dt);
	myObject->update(dt);

	/*camera movement*/
	if (up)
	{
		camera->moveCameraAlongY(-1.0f * dt);
	}
	if (down)
	{
		camera->moveCameraAlongY(1.0f * dt);
	}
	if (forwards)
	{
		camera->moveCameraAlongZ(-1.0f * dt);
	}
	if (backwards)
	{
		camera->moveCameraAlongZ(1.0f * dt);
	}
	if (left)
	{
		camera->moveCameraAlongX(-1.0f * dt);
	}
	if (right)
	{
		camera->moveCameraAlongX(1.0f * dt);
	}
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
	train->draw(camera->getView(), camera->getProjection());
	myObject->draw(camera->getView(), camera->getProjection());

	/*display the window*/
	SDL_GL_SwapWindow(window);
}