#pragma once

#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <memory>
#include "glew.h"
#include "Particle.h"

/**
@brief Creates a ParticleEffect object that handles Particle objects.
@author Jamie Slowgrove
*/
class ParticleEffect
{
private:
public:
	/**
	Constructs a ParticleEffect Object.
	*/
	ParticleEffect();

	/**
	Destructs a ParticleEffect Object.
	Destructs the ParticleEffect Object deleting the Particle Object from memory.
	*/
	~ParticleEffect();

	/**
	A function that updates the ParticleEffect
	@param dt The delta time.
	*/
	void update(float dt);
};
