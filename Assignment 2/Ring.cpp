#include "Ring.h"

/**************************************************************************************************************/

/*Constructs a Ring Object.*/
Ring::Ring(std::shared_ptr<Model> model, float scaleValue) : Entity(model, scaleValue)
{
}

/**************************************************************************************************************/

/*Destructs a Ring Object.*/
Ring::~Ring()
{
}

/**************************************************************************************************************/

/*update the ring*/
void Ring::update(float dt)
{
	/*set the position of the model*/
	model->setPosition(position);

	/*rotate the model*/
	model->rotate(rotation);

	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}