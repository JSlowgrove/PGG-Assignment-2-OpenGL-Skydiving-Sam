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
@brief Creates a Ground object that inherits Entity.
@author Jamie Slowgrove
*/
class Ground : public Entity
{
private:
public:
	/**
	Constructs a Ground Object.
	Creates a Ground Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param model A pointer to the model.
	@param scaleValue The scale of the Model.
	*/
	Ground(Model* model, float scaleValue);

	/**
	Destructs a Ground Object.
	Destructs the Ground Object deleting the Ground Object from memory.
	*/
	~Ground();

	/**
	A function that updates the Ring
	@param dt The delta time.
	*/
	void update(float dt);
};
