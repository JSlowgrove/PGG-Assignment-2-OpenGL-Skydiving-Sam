#include "MainMenu.h"
#include "Game.h"
#include "Credits.h"

/**************************************************************************************************************/

/*Constructs the MainMenu object*/
MainMenu::MainMenu(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*draw a loading screen*/
	loadingScreen();

	/*initialize random seed: */
	srand((unsigned int)time(NULL));

	/*Initialise the Camera*/
	camera = new Camera();

	/*create a menu entity from the sam model*/
	sam = new MenuEntity(new Model("default", "default", "sam", objects, shaders), 0.08f);
	
	/*set the background samurai's position*/
	sam->setPosition(0.0f, 0.0f, -2.5f);

	/*initialise the menu UI*/
	userInterface = new MainMenuUI("2d.default", "2d.default", shaders);

	/*initialise the top left particle effect*/
	particleEffects.push_back(new ParticleEffect("cube", objects, shaders, "default", "default",
		glm::vec3(0.0f, 0.0f, -2.5f), true));	

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
	delete sam;
	delete camera;
	delete userInterface;
	for (auto i = objects.begin(); i != objects.end(); ++i)
	{
		delete i->second;
	}
	for (auto i = shaders.begin(); i != shaders.end(); ++i)
	{
		delete i->second;
	}
	for (auto particleEffect : particleEffects)
	{
		delete particleEffect;
	}
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
					/*go to the credits state*/
					stateManager->addState(new Credits(stateManager, window, screenWidth, screenHeight, music));
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
	sam->update(dt);

	/*loop through all of the particle effects*/
	for (auto particleEffect : particleEffects)
	{
		/*get a random x position between -1.5 and 1.5*/
		float x = (float)((rand() % 30) - 15) * 0.1f;
		/*get a random y position between -1.5 and 1.5*/
		float y = (float)((rand() % 30) - 15) * 0.1f;

		/*update the particle effect*/
		particleEffect->makeNewParticles(objects, shaders);
		particleEffect->setEmitter(glm::vec3(x, y, -2.5f));
		particleEffect->update(dt);
	}	
}

/**************************************************************************************************************/

/*draws the game*/
void MainMenu::draw()
{
	/*Draw the samurai using the camera*/
	sam->draw(camera->getView(), camera->getProjection());

	/*loop through all of the particle effects*/
	for (auto particleEffect : particleEffects)
	{
		/*draw the particle effect*/
		particleEffect->draw(camera->getView(), camera->getProjection());
	}

	/*draw the UI*/
	userInterface->draw();
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