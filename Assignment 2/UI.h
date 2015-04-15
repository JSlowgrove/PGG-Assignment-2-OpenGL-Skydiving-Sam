#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Shader.h"
#include "UIObject.h"

/**
@brief
@author Jamie Slowgrove
*/
class UI
{
private:
	/**The shader for the UI*/
	Shader * shader;
	/**A UIObject for the score*/
	UIObject * score;
	/**A UIObject for the time*/
	UIObject * time;

	/**
	Initialise the shaders.
	@param std::string The name of the vertex shader file.
	@param std::string The name of the fragment shader file.
	@param std::unordered_map<std::string, Shader*> A reference to the loaded Shader files
	*/
	void initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders);

public:
	/**
	Constructs the UI object.
	@param std::string The name of the vertex shader file.
	@param std::string The name of the fragment shader file.
	@param std::unordered_map<std::string, Shader*> A reference to the loaded Shader files
	*/
	UI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders);

	/**
	Destructs the UI object.
	*/
	~UI();

	/**
	A function to update the UI.
	@param float The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};