#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Shader.h"
#include "UIObject.h"
#include "UI.h"

/**
@brief A class for the 2D HelpUI that inherits UI.
@author Jamie Slowgrove
*/
class HelpUI : public UI
{
private:
	/**The help image*/
	UIObject * help;

public:
	/**
	Constructs the HelpUI object.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	HelpUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders);

	/**
	Constructs the HelpUI object.
	@param textureName The name of the texture to load.
	@param shaders A reference to the loaded Shader files
	*/
	HelpUI(std::string textureName, std::unordered_map<std::string, Shader*> &shaders);

	/**
	Destructs the HelpUI object.
	*/
	~HelpUI();

	/**
	A function to update the HelpUI.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};