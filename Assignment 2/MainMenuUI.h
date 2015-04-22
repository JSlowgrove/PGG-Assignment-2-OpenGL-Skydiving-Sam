#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Shader.h"
#include "UIObject.h"
#include "UI.h"

/**
@brief A class for the 2D MainMenuUI that inherits UI.
@author Jamie Slowgrove
*/
class MainMenuUI : public UI
{
private:
	/**The Title Image*/
	UIObject * title;
	/**The Play Button*/
	UIObject * play;
	/**The Play Text*/
	UIObject * playText;
	/**The Credits Button*/
	UIObject * credits;
	/**The Credits Text*/
	UIObject * creditsText;
	/**The Quit Button*/
	UIObject * quit;
	/**The Quit Text*/
	UIObject * quitText;

public:
	/**
	Constructs the MainMenuUI object.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	@param shaders A reference to the loaded Shader files
	*/
	MainMenuUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
		std::unordered_map<std::string, Shader*> &shaders);

	/**
	Constructs the MainMenuUI object.
	@param shaders A reference to the loaded Shader files
	*/
	MainMenuUI(std::unordered_map<std::string, Shader*> &shaders);

	/**
	Destructs the MainMenuUI object.
	*/
	~MainMenuUI();

	/**
	A function to update the MainMenuUI.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};