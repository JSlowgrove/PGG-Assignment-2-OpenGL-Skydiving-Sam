#include "Ground.h"

/**************************************************************************************************************/

/*Constructs a Ground Object.*/
Ground::Ground(Model* model, float scaleValue) : Entity(model, scaleValue)
{
	/*initialise the move speed of the ground*/
	moveSpeed = 1.0f;
}

/**************************************************************************************************************/

/*Destructs a Ground Object.*/
Ground::~Ground()
{
	/*delete the pointers*/
	delete model;
}

/**************************************************************************************************************/

/*update the ground*/
void Ground::update(float dt)
{
	/*move the ground towards the camera*/
	moveZ(moveSpeed * dt);

	/*set the position of the model*/
	model->setPosition(position);

	/*rotate the model*/
	model->rotate(rotation);

	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}