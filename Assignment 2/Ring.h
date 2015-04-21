#pragma once

#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <memory>
#include "glew.h"
#include "Utilities.h"
#include "Entity.h"

/**
@brief Creates a Ring object that inherits Entity.
@author Jamie Slowgrove
*/
class Ring : public Entity
{
private:
	/**The type of AI that the Ring will use*/
	int AI;
	/**The move speed for the AI*/
	float moveSpeedAI;
	/**The scale speed for the AI*/
	float scaleSpeedAI;
	/**Angle for the position of the ring on the circle (use with AI type 4)*/
	float circleAngle;
	/**Radius for the circle (use with AI type 4)*/
	float circleRadius;
	/**The XY move direction for the rings*/
	glm::vec2 directionXY;
	/**The scale direction*/
	float scaleDirection;
	
public:
	/**
	Constructs a Ring Object.
	Creates a Ring Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param model A pointer to the model.
	@param scaleValue The scale of the Model.
	@param AI The Ring AI type (number between 0 and 6).
	*/
	Ring(Model* model, float scaleValue, int AI);

	/**
	Destructs a Ring Object.
	Destructs the Ring Object deleting the Ring Object from memory.
	*/
	~Ring();

	/**
	A function that updates the Ring
	@param dt The delta time.
	*/
	void update(float dt);
	
	/**
	Apply the action of AI type 0.
	The ring does nothing.
	@param dt The delta time.
	*/
	void typeZeroAI(float dt);
	
	/**
	Apply the action of AI type 1.
	The ring moves right and left.
	@param dt The delta time.
	*/
	void typeOneAI(float dt);
	
	/**
	Apply the action of AI type 2.
	The ring moves forwards and backwards.
	@param dt The delta time.
	*/
	void typeTwoAI(float dt);
	
	/**
	Apply the action of AI type 3.
	The ring moves scales up and down.
	@param dt The delta time.
	*/
	void typeThreeAI(float dt);
	
	/**
	Apply the action of AI type 4.
	The ring moves in a circle.
	@param dt The delta time.
	*/
	void typeFourAI(float dt);
};
