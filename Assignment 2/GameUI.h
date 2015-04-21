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

public:
	/**
	Constructs the GameUI object.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	GameUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders);

	/**
	Constructs the GameUI object.
	@param shaders A reference to the loaded Shader files
	*/
	GameUI(std::unordered_map<std::string, Shader*> &shaders);

	/**
	Destructs the GameUI object.
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
};