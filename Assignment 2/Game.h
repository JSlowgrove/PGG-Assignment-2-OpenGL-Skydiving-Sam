#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <time.h>
#include "Utilities.h"
#include "State.h"
#include "StateManager.h"
#include "Audio.h"
#include "Camera.h"
#include "Entity.h"
#include "GameUI.h"
#include "LoadingScreen.h"
#include "Ring.h"
#include "Player.h"
#include "Ground.h"
#include "HelpUI.h"
#include "ParticleEffect.h"


/**A definition of the number of target rings*/
#define NUM_OF_TARGETS 30

/**
@brief Creates an Game object that inherits State and runs the Game.
@author Jamie Slowgrove
*/
class Game : public State
{
private:
	/**The loaded Object files*/
	std::unordered_map<std::string, Object*> objects;
	/*The loaded Shader files*/
	std::unordered_map<std::string, Shader*> shaders;
	/**The background music*/
	Audio* music;
	/**The sound effect for passing the rings*/
	Audio* ringPassed;
	/**The sound effect for missing the rings*/
	Audio* ringMissed;
	/**A vector of the target Ring objects*/
	std::vector<Ring*> targetRings;
	/**The Player Entity*/
	Player* player;
	/**The Ground Entity*/
	Ground* ground;
	/**The Camera for the Game*/
	Camera* camera;
	/**The GameUI*/
	GameUI* userInterface;
	/**The height that the Player is from the Ground.*/
	float height;
	/**The score of the Player. 
	Lowest score is best. 
	Score increases with time and decreases when a ring is gone through.*/
	float score;
	/**A int for the number of initial loops before the game should update*/
	int initialLoops;
	/**A ParticleEffect for when the player passes the last ring*/
	ParticleEffect* reachedEndEffect;
	/**The time since the player reached the end*/
	float timeSinceEnd;

	/**
	Draws a LoadingScreen.
	*/
	void loadingScreen();

public:
	/**
	Constructs a Game object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	*/
	Game(StateManager* stateManager, SDL_Window* window, int screenWidth, int screenHeight);

	/**
	Destructs an Game object.
	*/
	~Game();

	/**
	Handles the Game input.
	@returns If false then quit the Game State.
	*/
	bool input();

	/**
	A function to update the Game.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};