#include "Particle.h"

/**************************************************************************************************************/

/*Constructs a Particle Object.*/
Particle::Particle(Model* model, float scaleValue, float direction, float moveSpeed) : Entity(model, scaleValue)
{
	/*initialise the direction*/
	this->direction;
	/*initialise the moveSpeed*/
	this->moveSpeed;
}

/**************************************************************************************************************/

/*Destructs a Particle Object.*/
Particle::~Particle()
{
	/*delete the pointers*/
	delete model;
}

/**************************************************************************************************************/

/*update the ground*/
void Particle::update(float dt)
{
	/*update the position of the particle*/
	move(direction * moveSpeed * dt);

	/*set the position of the model*/
	model->setPosition(position);

	/*rotate the model*/
	model->rotate(rotation);

	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}