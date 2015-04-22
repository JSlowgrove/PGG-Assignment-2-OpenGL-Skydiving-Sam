#include "Game.h"
#include "MainMenu.h"
#include "Help.h"
#include "EndGame.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(StateManager * stateManager, SDL_Window* window, int screenWidth, int screenHeight)
	: State(stateManager, window, screenWidth, screenHeight)
{
	/*initialise the number of initial loops*/
	initialLoops = 2;

	/*draw a loading screen*/
	loadingScreen();

	/*Initialise the Camera*/
	camera = new Camera();

	/*initialize random seed: */
	srand((unsigned int)time(NULL));

	/*create a player entity using the sam model*/
	player = new Player(new Model("texture", "texture", "sam", objects, shaders, "sam.png"), 0.015f);

	/*loop for the number of ring targets*/
	for (int i = 0; i < NUM_OF_TARGETS; i++)
	{
		/*get a random scale between 0.08f and 0.25f*/
		float scaleValue = (float)((rand() % 18) + 8) * 0.01f;
		/*get a random AI type between 0 and 4*/
		int AI = rand() % 5;
		/*push a new Ring entity using a ring model to the targetRings vector*/
		targetRings.push_back(new Ring(new Model("default", "green", "ring", objects, shaders), scaleValue, AI));
	}

	/*create a ground entity using a shopping centre model*/
	ground = new Ground(new Model("default", "default", "shoppingCentre", objects, shaders), 0.05f);
	
	/*set the initial entity positions*/
	player->setPosition(0.0f, 0.0f, 0.0f);
	/*loop for the number of ring targets*/
	for (int i = 0; i < NUM_OF_TARGETS; i++)
	{
		/*get a random x position between -1.5 and 1.5*/
		float x = (float)((rand() % 30) - 15) * 0.1f;
		/*get a random y position between -1.5 and 1.5*/
		float y = (float)((rand() % 30) - 15) * 0.1f;
		/*work out the z position*/
		float z = -10.0f - (i * 5.0f);
		/*initialise the position*/
		targetRings[i]->setPosition(x, y, z);
	}
	/*work out the z position for the ground*/
	float z = -10.0f - (NUM_OF_TARGETS * 5.0f);
	ground->setPosition(-1.0f, 1.0f, z);

	/*set the initial entity rotations*/
	player->rotateY(Utilities::convertAngleToRadian(180.0f));
	/*loop through all the ring targets*/
	for (auto targetRing : targetRings)
	{
		targetRing->rotateX(Utilities::convertAngleToRadian(90.0f));
	}
	ground->rotateX(Utilities::convertAngleToRadian(90.0f));

	/*initialise the height*/
	height = 0.0f;

	/*initialise the score*/
	score = 0.0f;

	/*initialise the UI*/
	userInterface = new GameUI(shaders, height, score);

	/*initialise the particle effect*/
	reachedEndEffect = new ParticleEffect("cube", objects, shaders, "default", "default",
		glm::vec3(0.0f, 0.0f, 0.0f), false);

	/*stop the loading music*/
	music->stopAudio();

	/*initialise and start the music*/
	music = new Audio("aud/Harmful or Fatal.ogg", true);
	music->startAudio();

	/*initialise the sound effects*/
	ringPassed = new Audio("aud/threeTone2.ogg", false);
	ringMissed = new Audio("aud/zapThreeToneDown.ogg", false);

	/*initialise the time since the end*/
	timeSinceEnd = 0.0f;

	/*initialise the ended bool to false*/
	ended = false;
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	/*stop music*/
	music->stopAudio();
	/*delete audio pointers*/
	delete music;
	delete ringPassed;
	delete ringMissed;
	/*delete pointers*/
	delete camera;
	delete player;
	delete ground;
	delete userInterface;
	delete reachedEndEffect;
	for (auto targetRing : targetRings)
	{
		delete targetRing;
	}
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
			case SDLK_RETURN: /*If enter is pressed the game opens the help state*/

				/*reset the player commands*/
				player->resetCommands();
				/*go to the help state*/
				stateManager->addState(new Help(stateManager, window, screenWidth, screenHeight, music));
				break;
			}
			break;
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
	/*if it is one of the initial loops*/
	if (initialLoops != 0)
	{
		/*set the dt to 0.0f to counter the large initial load time*/
		dt = 0.0f;
		/*decrease the number of initial loops*/
		initialLoops--;
	}
	
	/*if the game has ended*/
	if (ended)
	{
		/*reset the game*/
		resetGame();
	}

	/*keep the music playing*/
	music->startAudio();

	/*if not all of the rings have been passed*/
	if (targetRings.size() > 0)
	{
		/*Update the player*/
		player->update(dt);

		/*update the ground speed*/
		ground->setMoveSpeed(player->getWorldSpeed());

		/*Update the ground*/
		ground->update(dt);

		/*update the height value*/
		height = -ground->getPosition().z * 10.0f;

		/*update the score*/
		score += dt * 10.0f;
	}
	else
	{
		/*update the time since the end*/
		timeSinceEnd += dt;

		/*if it have been less than half a second since the end was reached*/
		if (timeSinceEnd < 0.5f)
		{
			/*set the particle effect to true*/
			reachedEndEffect->setEmitting(true);
		}
		else
		{
			/*set the particle effect to false*/
			reachedEndEffect->setEmitting(false);
		}

		/*if it have been greater than 1.5f seconds since the end was reached*/
		if (timeSinceEnd > 1.5f)
		{
			/*Open the game over state*/
			stateManager->addState(new EndGame(stateManager, window, screenWidth, screenHeight, music, score));

			/*set ended to true*/
			ended = true;
		}
	}

	/*update the particle effect*/
	reachedEndEffect->makeNewParticles(objects, shaders);
	reachedEndEffect->setEmitter(player->getPosition());
	reachedEndEffect->update(dt);

	/*loop through all of the target rings*/
	for (unsigned int i = 0; i < targetRings.size(); i++)
	{
		/*update the target ring speed*/
		targetRings[i]->setMoveSpeed(player->getWorldSpeed());
		/*Update the target ring*/
		targetRings[i]->update(dt);

		/*if the ring at the same level as the player*/
		if (targetRings[i]->getPosition().z >= player->getPosition().z)
		{
			/*equation of a circle is x^2 + y^2 = r^2.
			Therefore if the (player.x - ring.x)^2 - (player.y - ring.y)^2 is less than
			the ring's radius squared, it is inside the ring*/

			/*get the x^2*/
			float xSquared = (player->getPosition().x - targetRings[i]->getPosition().x) * (player->getPosition().x - targetRings[i]->getPosition().x);
			/*get the y^2*/
			float ySquared = (player->getPosition().y - targetRings[i]->getPosition().y) * (player->getPosition().y - targetRings[i]->getPosition().y);
			/*get the r^2*/
			float rSquared = xSquared + ySquared;

			/*work out the r of the ring*/
			float ringR = 5.318f * targetRings[i]->getScale();
			/*work out the r^2 of the ring*/
			float ringRSquared = ringR * ringR;

			/*test if the player is inside the ring*/
			if (rSquared < ringRSquared)
			{
				/*play the sound effect*/
				ringPassed->playEffect();
			}
			else
			{
				/*play the sound effect*/
				ringMissed->playEffect();

				/*increase the score*/
				score += 50.0f;
			}

			/*remove the ring*/
			targetRings.erase(targetRings.begin() + i);
		}
	}
	/*update the game UI*/
	userInterface->updateValues(score, height);
	userInterface->update(dt);

	/*update the camera position*/
	camera->setPosition(glm::vec3(-player->getPosition().x, -player->getPosition().y, -1.5f));
}

/**************************************************************************************************************/

/*draws the game*/
void Game::draw()
{
	/*if not all of the rings have been passed*/
	if (targetRings.size() > 0)
	{
		/*Draw the player using the camera*/
		player->draw(camera->getView(), camera->getProjection());
	}

	/*loop through all of the target rings*/
	for (auto targetRing : targetRings)
	{
		/*Draw the target ring using the camera*/
		targetRing->draw(camera->getView(), camera->getProjection());
	}

	/*Draw the ground using the camera*/
	ground->draw(camera->getView(), camera->getProjection());

	/*draw the particle effect*/
	reachedEndEffect->draw(camera->getView(), camera->getProjection());

	/*draw the UI*/
	userInterface->draw();
}

/**************************************************************************************************************/

/*Draws a LoadingScreen.*/
void Game::loadingScreen()
{
	/*initialise and start the loading music*/
	music = new Audio("aud/Cut Trance.ogg", true);
	music->startAudio();

	/*create the loading screen*/
	LoadingScreen * loadingScreen = new LoadingScreen(shaders);

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

/**************************************************************************************************************/

/*Resets the Game*/
void Game::resetGame()
{
	/*loop for the number of ring targets*/
	for (int i = 0; i < NUM_OF_TARGETS; i++)
	{
		/*get a random scale between 0.08 and 0.25*/
		float scaleValue = (float)((rand() % 18) + 8) * 0.01f;
		/*get a random AI type between 0 and 4*/
		int AI = rand() % 5;
		/*push a new Ring entity using a ring model to the targetRings vector*/
		targetRings.push_back(new Ring(new Model("default", "green", "ring", objects, shaders), scaleValue, AI));
	}

	/*set the initial entity positions*/
	player->setPosition(0.0f, 0.0f, 0.0f);

	/*loop for the number of ring targets*/
	for (int i = 0; i < NUM_OF_TARGETS; i++)
	{
		/*get a random x position between -1.5 and 1.5*/
		float x = (float)((rand() % 30) - 15) * 0.1f;
		/*get a random y position between -1.5 and 1.5*/
		float y = (float)((rand() % 30) - 15) * 0.1f;
		/*work out the z position*/
		float z = -10.0f - (i * 5.0f);
		/*initialise the position*/
		targetRings[i]->setPosition(x, y, z);
	}

	/*work out the z position for the ground*/
	float z = -10.0f - (NUM_OF_TARGETS * 5.0f);
	ground->setPosition(-1.0f, 1.0f, z);

	/*loop through all the ring targets*/
	for (auto targetRing : targetRings)
	{
		targetRing->rotateX(Utilities::convertAngleToRadian(90.0f));
	}

	/*initialise the height*/
	height = 0.0f;

	/*initialise the score*/
	score = 0.0f;

	/*reset the game UI*/
	userInterface->updateValues(score, height);
	
	/*initialise the time since the end*/
	timeSinceEnd = 0.0f;

	/*initialise the ended bool to false*/
	ended = false;
}