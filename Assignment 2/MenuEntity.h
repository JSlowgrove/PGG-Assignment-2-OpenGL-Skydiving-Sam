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
@brief Creates a MenuEntity that inherits Entity.
@author Jamie Slowgrove
*/
class MenuEntity : public Entity
{
private:
public:
	/**
	Constructs a MenuEntity Object.
	Creates a Entity Object with a Model using the shader file locations, the obj file location and OpenGL.
	@param model A shared pointer to the model.
	@param scale The scale of the Model.
	*/
	MenuEntity(std::shared_ptr<Model> model, float scale);

	/**
	Destructs a MenuEntity Object.
	Destructs the MenuEntity Object deleting the MenuEntity Object from memory.
	*/
	~MenuEntity();

	/**
	Updates the MenuEntity.
	@param dt The delta time.
	*/
	void update(float dt);
};
