#include "Game.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*Initialise the Camera*/
	camera = new Camera();
	
	// Create a train model
	std::shared_ptr<Model> model;
	model.reset(new Model("default", "default", "train", objects, shaders));
	train = new Entity(model, 0.2f);
	
	// Create a car model
	model.reset(new Model("default", "default", "car", objects, shaders));
	car = new Entity(model, 0.002f);
	car->rotateY(Utilities::convertAngleToRadian(270));

	// Create a second train model
	model.reset(new Model("default", "default", "train", objects, shaders));
	train2 = new Entity(model, 0.2f);
	train2->rotateY(Utilities::convertAngleToRadian(90));

	// Create a second car model
	model.reset(new Model("default", "default", "car", objects, shaders));
	car2 = new Entity(model, 0.002f);

	// Set object's position like this:
	train->setPosition(0.0f, 0.0f, 0.0f);
	car->setPosition(0.0f, -0.5f, 0.0f);
	train2->setPosition(0.0f, 0.0f, 0.0f);
	car2->setPosition(0.0f, -0.5f, 0.0f);

	/*initialise the camera movement*/
	up = down = left = right = forwards = backwards = false;
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	/*delete pointers*/
	delete train;
	delete car;
	delete train2;
	delete car2;
	delete camera;
	for (auto i = objects.begin(); i != objects.end(); ++i)
	{
		delete i->second;
	}
	for (auto i = shaders.begin(); i != shaders.end(); ++i)
	{
		delete i->second;
	}
}

/**************************************************************************************************************/

/*handles inputs*/
bool Game::input()
{
	/*Check for user input*/
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		/*update the mouse position*/
		mouse.x = ((float)incomingEvent.motion.x);
		mouse.y = ((float)incomingEvent.motion.y);
		
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

			case SDLK_w: /*If w/up is pressed, forwards is true*/
			case SDLK_UP:
				forwards = true;
				break;

			case SDLK_s: /*If s/down is pressed, backwards is true*/
			case SDLK_DOWN:
				backwards = true;
				break;

			case SDLK_a: /*If a/left is pressed, left is true*/
			case SDLK_LEFT:
				left = true;
				break;

			case SDLK_d: /*If s/right is pressed, right is true*/
			case SDLK_RIGHT:
				right = true;
				break;
			}
			break;

		case SDL_KEYUP:

			switch (incomingEvent.key.keysym.sym)
			{

			case SDLK_w: /*If w/up is pressed, forwards is false*/
			case SDLK_UP: 
				forwards = false;
				break;

			case SDLK_s: /*If s/down is pressed, backwards is false*/
			case SDLK_DOWN:
				backwards = false;
				break;

			case SDLK_a: /*If a/left is pressed, left is false*/
			case SDLK_LEFT:
				left = false;
				break;

			case SDLK_d: /*If d/right is pressed, right is false*/
			case SDLK_RIGHT:
				right = false;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN: 

			/*If left mouse is pressed, down is true*/
			if (incomingEvent.button.button == SDL_BUTTON_LEFT)
			{
				down = true;
			}

			/*If right mouse is pressed, up is true*/
			if (incomingEvent.button.button == SDL_BUTTON_RIGHT)
			{
				up = true;
			}

			break;

		case SDL_MOUSEBUTTONUP:

			/*If left mouse is released, down is false*/
			if (incomingEvent.button.button == SDL_BUTTON_LEFT)
			{
				down = false;
			}

			/*If right mouse is released, up is false*/
			if (incomingEvent.button.button == SDL_BUTTON_RIGHT)
			{
				up = false;
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
	car->update(dt);
	train2->update(dt);
	car2->update(dt);

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
	car->draw(camera->getView(), camera->getProjection());
	train2->draw(camera->getView(), camera->getProjection());
	car2->draw(camera->getView(), camera->getProjection());

	/*display the window*/
	SDL_GL_SwapWindow(window);
}