#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Shader.h"
#include "UIObject.h"
#include "UI.h"

/**
@brief A class for the 2D GameUI that inherits UI.
@author Jamie Slowgrove
*/
class GameUI : public UI 
{
private:
	/**A UIObject for the score*/
	UIObject * score;
	/**A UIObject for the height from the ground*/
	UIObject * height;
	/**A UIObject for how to open the help screen or quit to menu*/
	UIObject * helpInfo;
	/**A UIObject for the score text*/
	UIObject * scoreText;
	/**A UIObject for the height text*/
	UIObject * heightText;
	/**The score of the game*/
	float scoreValue;
	/**The height of the game*/
	float heightValue;

public:
	/**
	Constructs the GameUI object.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	@param scoreValue The score.
	@param heightValue The height.
	*/
	GameUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders, float scoreValue, float heightValue);

	/**
	Constructs the GameUI object.
	@param shaders A reference to the loaded Shader files.
	@param scoreValue The score.
	@param heightValue The height.
	*/
	GameUI(std::unordered_map<std::string, Shader*> &shaders, float scoreValue, float heightValue);

	/**
	Destructs the GameUI object
	*/
	~GameUI();

	/**
	A function to update the GameUI.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();

	/**
	A function to update the score and height in the GameUI.
	@param scoreValue The score.
	@param heightValue The height.
	*/
	void updateValues(float scoreValue, float heightValue);
};