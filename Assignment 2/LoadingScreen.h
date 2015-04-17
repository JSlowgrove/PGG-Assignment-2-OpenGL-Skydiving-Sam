#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Shader.h"
#include "UIObject.h"
#include "UI.h"

/**
@brief A class for the 2D LoadingScreen that inherits UI.
@author Jamie Slowgrove
*/
class LoadingScreen : public UI
{
private:
	/**The loading text*/
	UIObject * loadingText;
	/**The loading image*/
	UIObject * loadingImage;

public:
	/**
	Constructs the LoadingScreen object.
	@param std::string The name of the vertex shader file.
	@param std::string The name of the fragment shader file.
	@param std::unordered_map<std::string, Shader*> A reference to the loaded Shader files
	*/
	LoadingScreen(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders);

	/**
	Destructs the LoadingScreen object.
	*/
	~LoadingScreen();

	/**
	A function to update the LoadingScreen.
	@param float The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};