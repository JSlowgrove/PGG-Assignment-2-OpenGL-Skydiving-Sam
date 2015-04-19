#include "MenuEntity.h"

/**************************************************************************************************************/

/*Constructs a MenuEntity Object.*/
MenuEntity::MenuEntity(Model* model, float scale) : Entity(model, scale)
{
}

/**************************************************************************************************************/

/*Destructs a MenuEntity Object.*/
MenuEntity::~MenuEntity()
{
	/*delete the pointers*/
	delete model;
}

/**************************************************************************************************************/

/*update the MenuEntity*/
void MenuEntity::update(float dt)
{
	/*update the rotation of the model*/
	rotation.y += dt * 0.5f;
	
	/*make sure that the rotation is between 0 and 2PI*/
	while (rotation.y > (Utilities::getPI() * 2.0))
	{
		rotation.y -= (float)(Utilities::getPI() * 2.0f);
	}
	
	/*set the position of the model*/
	model->setPosition(position);

	/*rotate the model*/
	model->rotate(rotation);

	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}