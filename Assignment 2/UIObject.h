#pragma once

#include <iostream>
#include <glm.hpp>
#include <SDL.h>
#include "Shader.h"

/**
@brief A class for the UI Objects.
@author Jamie Slowgrove
*/
class UIObject
{
private:
	/**The VBO for the rectangle*/
	GLuint obj;
	/**The dimensions for the rectangle*/
	glm::vec2 dimensions;
	/**The position for the UIObject*/
	glm::vec2 position;
	/**The Texture*/
	GLuint textureID;
	/**A boolean for if the Model contains a texture*/
	bool textureBool;

	/**
	Initialise the UIobject.
	*/
	void initialiseObject();

	/**
	Initialise the UIobject.
	@param surface A pointer to the surface for the texture.
	*/
	void initialiseObject(SDL_Surface* surface);

	/**
	Initialise the texture.
	@param surface A pointer to the surface for the texture.
	*/
	void initialiseTexture(SDL_Surface* surfac);

	/**
	Converts the coordinates to work with OpenGL.
	It takes the coordinates and converts them to a number between 0 and 2.
	It then takes this and -1 from each, setting it to the bottom left position.
	It then flips the coordinate along the y axis to get the top left position.
	@param coordinates The coordinates to convert.
	@returns The converted coordinates.
	*/
	glm::vec2 convertToOpenGLCoordinate(glm::vec2 coordinates);

public:
	/**
	Constructs the UIObject.
	@param x The x position (Top left of the object).
	@param y The y position (Top left of the object).
	@param width The width (Between 0 and 200).
	@param height The height (Between 0 and 200).
	*/
	UIObject(float x, float y, float width, float height);

	/**
	Constructs the UIObject.
	@param x The x position (Top left of the object).
	@param y The y position (Top left of the object).
	@param width The width (Between 0 and 200).
	@param height The height (Between 0 and 200).
	@param surface A pointer to the surface for the texture.
	*/
	UIObject(float x, float y, float width, float height, SDL_Surface* surface);

	/**
	Destructs the UIObject.
	*/
	~UIObject();

	/**
	A function to draw to the screen.
	@param shader A pointer to the Shader to use.
	*/
	void draw(Shader * shader);
};