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
public:
	/**
	Constructs a Ring Object.
	Creates a Ring Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param model A pointer to the model.
	@param scaleValue The scale of the Model.
	*/
	Ring(Model* model, float scaleValue);

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
};
