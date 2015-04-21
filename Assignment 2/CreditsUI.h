#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Shader.h"
#include "UIObject.h"
#include "UI.h"

/**
@brief A class for the 2D CreditsUI that inherits UI.
@author Jamie Slowgrove
*/
class CreditsUI : public UI
{
private:
	/**The credits image*/
	UIObject * credits;

public:
	/**
	Constructs the CreditsUI object.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	CreditsUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders);

	/**
	Constructs the CreditsUI object.
	@param shaders A reference to the loaded Shader files
	*/
	CreditsUI(std::unordered_map<std::string, Shader*> &shaders);

	/**
	Destructs the CreditsUI object.
	*/
	~CreditsUI();

	/**
	A function to update the CreditsUI.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};