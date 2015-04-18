#pragma once

#include <iostream>
#include <glm.hpp>
#include "Shader.h"

/**
@brief
@author Jamie Slowgrove
*/
class UIObject
{
private:
	/**The VBO for the rectangle*/
	GLuint obj;
	/*The dimensions for the rectangle*/
	glm::vec2 dimensions;
	/*The position for the UIObject*/
	glm::vec2 position;

	/**
	Initialise the UIobject.
	*/
	void initialiseObject();

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
	Destructs the UIObject.
	*/
	~UIObject();

	/**
	A function to draw to the screen.
	@param shader A pointer to the Shader to use.
	*/
	void draw(Shader * shader);
};