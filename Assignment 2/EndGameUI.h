#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Shader.h"
#include "UIObject.h"
#include "UI.h"

/**
@brief A class for the 2D EndGameUI that inherits UI.
@author Jamie Slowgrove
*/
class EndGameUI : public UI
{
private:
	/**The end game image*/
	UIObject * endGame;
	/**A UIObject for the score text*/
	UIObject * scoreText;

public:
	/**
	Constructs the EndGameUI object.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	@param scoreValue The score.
	*/
	EndGameUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders, float score);

	/**
	Constructs the EndGameUI object.
	@param shaders A reference to the loaded Shader files
	@param scoreValue The score.
	*/
	EndGameUI(std::unordered_map<std::string, Shader*> &shaders, float score);

	/**
	Destructs the EndGameUI object.
	*/
	~EndGameUI();

	/**
	A function to update the EndGameUI.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};