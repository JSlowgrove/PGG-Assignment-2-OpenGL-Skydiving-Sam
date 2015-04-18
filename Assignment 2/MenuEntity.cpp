#include "MenuEntity.h"

/**************************************************************************************************************/

/*Constructs a MenuEntity Object.*/
MenuEntity::MenuEntity(std::shared_ptr<Model> model, float scale) : Entity(model, scale)
{
}

/**************************************************************************************************************/

/*Destructs a MenuEntity Object.*/
MenuEntity::~MenuEntity()
{
}

/**************************************************************************************************************/

/*update the MenuEntity*/
void MenuEntity::update(float deltaTs)
{
	// update the rotation angle of our cube
	rotation.y += deltaTs * 0.5f;
	while (rotation.y > (Utilities::getPI() * 2.0))
	{
		rotation.y -= (float)(Utilities::getPI() * 2.0f);
	}

	// Build the model matrix!
	// First we start with an identity matrix
	// This is created with the command: glm::mat4(1.0f)
	// Next, we translate this matrix according to the object's _position vector:
	model->setPosition(position);
	// Next, we rotate this matrix in the y-axis by the object's y-rotation:
	model->rotateY(rotation.y);
	// And there we go, model matrix is ready!

	/*scale the model*/
	model->scale(glm::vec3(scale, scale, scale));
}