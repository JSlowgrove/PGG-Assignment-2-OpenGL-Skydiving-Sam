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

public:
	/**
	Constructs the EndGameUI object.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	EndGameUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders);

	/**
	Constructs the EndGameUI object.
	@param textureName The name of the texture to load.
	@param shaders A reference to the loaded Shader files
	*/
	EndGameUI(std::string textureName, std::unordered_map<std::string, Shader*> &shaders);

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