#include "MainMenu.h"
#include "Game.h"

/**************************************************************************************************************/

/*Constructs the MainMenu object*/
MainMenu::MainMenu(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*draw a loading screen*/
	loadingScreen();

	/*Initialise the Camera*/
	camera = new Camera();

	/*create a samurai model*/
	std::shared_ptr<Model> model;
	model.reset(new Model("default", "default", "samurai", objects, shaders));

	/*create a menu entity from the model*/
	samurai = new MenuEntity(model, 0.5f);
	
	/*set the background samurai's position*/
	samurai->setPosition(0.0f, -1.0f, 0.0f);

	/*initialise the menu UI*/
	userInterface = new MainMenuUI("2d.default", "2d.default", shaders);

	/*initialise the mouse*/
	mouse = glm::vec2(0.0f, 0.0f);

	/*initialise the keys to 0*/
	playKey = credKey = exitKey = 0;

	/*initialise to not pressed*/
	pressed = 0;

	/*stop the loading music*/
	music->stopAudio();

	/*initialise and start the music*/
	music = new Audio("aud/Cool Hard Facts.ogg", true);
	music->startAudio();
}

/**************************************************************************************************************/

/*Destructs the MainMenu object*/
MainMenu::~MainMenu()
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
bool MainMenu::input()
{
	/*Check for user input*/
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		/*get the mouse input*/
		mouse.x = ((float)incomingEvent.motion.x);
		mouse.y = ((float)incomingEvent.motion.y);

		/*****************************************************
		The values of the positions below are worked out via: 
		(num/200)*640 for the x values,
		(num/200)*480 for the y values.
		******************************************************/

		/*a ternary operator checking if the mouse is above the play key*/
		playKey = (mouse.x > 240.0f && mouse.x < 400.0f && mouse.y > 240.0f && mouse.y < 288.0f) ? 1 : 0;
		/*a ternary operator checking if the mouse is above the credits key*/
		credKey = (mouse.x > 240.0f && mouse.x < 400.0f && mouse.y > 300.0f && mouse.y < 348.0f) ? 1 : 0;
		/*a ternary operator checking if the mouse is above the exit key*/
		exitKey = (mouse.x > 240.0f && mouse.x < 400.0f && mouse.y > 360.0f && mouse.y < 408.0f) ? 1 : 0;
		
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

		case SDL_MOUSEBUTTONDOWN: /*If the mouse is pressed*/
			/*if the left mouse button set the x and y to the current mouse position*/
			if (incomingEvent.button.button == SDL_BUTTON_LEFT)
			{
				/*if play key is highlighted*/
				if (playKey == 1)
				{
					/*set pressed to 1*/
					pressed = 1;
				}

				/*if credits key is highlighted*/
				if (credKey == 1)
				{
					/*set pressed to 2*/
					pressed = 2;
				}

				/*if exit key is highlighted*/
				if (exitKey == 1)
				{
					/*set pressed to 3*/
					pressed = 3;
				}

				/*if no key is highlighted*/
				if (playKey == 0 && credKey == 0 && exitKey == 0)
				{
					/*set pressed to 0*/
					pressed = 0;
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:/*If the mouse is released*/
			/*if the left mouse button*/
			if (incomingEvent.button.button == SDL_BUTTON_LEFT)
			{
				switch (pressed)
				{
				case 1:
					/*stop music*/
					music->stopAudio();
					/*go to the game state*/
					stateManager->changeState(new Game(stateManager, window, screenWidth, screenHeight));
					return true;
					break;
				case 2:
					/*open up the credits*/
					break;
				case 3:
					/*exit the application*/
					return false;
					break;
				}
			}
			break;
		}
	}
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void MainMenu::update(float dt)
{
	/*keep the music playing*/
	music->startAudio();

	/*update the background model*/
	samurai->update(dt);
}

/**************************************************************************************************************/

/*draws the game*/
void MainMenu::draw()
{
	/*clear the frame-buffer to a colour*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/*write colour to the frame-buffer*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*Draw the samurai using the camera*/
	samurai->draw(camera->getView(), camera->getProjection());

	/*draw the UI*/
	userInterface->draw();

	/*display the window*/
	SDL_GL_SwapWindow(window);
}

/**************************************************************************************************************/

/*Draws a LoadingScreen.*/
void MainMenu::loadingScreen()
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