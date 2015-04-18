#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Shader.h"
#include "UIObject.h"

/**
@brief A class for the 2D user interfaces.
@author Jamie Slowgrove
*/
class UI
{
protected:
	/**The shader for the UI*/
	Shader * shader;

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
	Constructs the UI object.
	@param std::string The name of the texture to load.
	@param std::unordered_map<std::string, Shader*> A reference to the loaded Shader files
	*/
	UI(std::string textureName, std::unordered_map<std::string, Shader*> &shaders);

	/**
	Destructs the UI object.
	*/
	~UI();

	/**
	A pure virtual function to update the UI.
	@param float The delta time.
	*/
	virtual void update(float dt) = 0;

	/**
	A pure virtual function to draw to the screen.
	*/
	virtual void draw() = 0;
};