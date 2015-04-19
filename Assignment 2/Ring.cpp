#include "Ring.h"

/**************************************************************************************************************/

/*Constructs a Ring Object.*/
Ring::Ring(Model* model, float scaleValue) : Entity(model, scaleValue)
{
	/*initialise the move speed of the ring*/
	moveSpeed = 1.0f;
}

/**************************************************************************************************************/

/*Destructs a Ring Object.*/
Ring::~Ring()
{
	/*delete the pointers*/
	delete model;
}

/**************************************************************************************************************/

/*update the ring*/
void Ring::update(float dt)
{
	/*move the ring towards the camera*/
	moveZ(moveSpeed * dt);

	/*set the position of the model*/
	model->setPosition(position);

	/*rotate the model*/
	model->rotate(rotation);

	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}