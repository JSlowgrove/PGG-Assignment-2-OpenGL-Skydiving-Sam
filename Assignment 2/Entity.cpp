#include "Entity.h"

/**************************************************************************************************************/

/*Constructs a Entity Object.*/
Entity::Entity(Model* model, float scaleValue)
{
	/*initialise the model*/
	this->model = model;
	/*initialise the rotation*/
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	/*set the scale of the model*/
	this->scaleValue = scaleValue;
	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}

/**************************************************************************************************************/

/*Destructs a Entity Object.*/
Entity::~Entity()
{
}

/**************************************************************************************************************/

/*Draw the Entity to the screen.*/
void Entity::draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	/*draw the model to the screen*/
	model->draw(viewMatrix, projMatrix);
}

/**************************************************************************************************************/

/*Sets the position of the Entity.*/
void Entity::setPosition(glm::vec3 position)
{
	/*set the position*/
	this->position = position;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Sets the position of the Entity.*/
void Entity::setPosition(float x, float y, float z)
{
	/*set the x position*/
	position.x = x;
	/*set the y position*/
	position.y = y;
	/*set the z position*/
	position.z = z;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Rotate the Entity along the X axis.*/
void Entity::rotateX(float angle)
{
	/*rotate the model*/
	model->rotateX(angle);
	/*set the value of rotation*/
	rotation.x += angle;
	/*make sure the stored rotation is within 0 and 2PI*/
	while (rotation.x > 2.0f * Utilities::getPI())
	{
		rotation.x -= 2.0f * Utilities::getPI();
	}
	while (rotation.x < 0.0f)
	{
		rotation.x += 2.0f * Utilities::getPI();
	}
}

/**************************************************************************************************************/

/*Rotate the Entity along the Y axis.*/
void Entity::rotateY(float angle)
{
	/*rotate the model*/
	model->rotateY(angle);
	/*set the value of rotation*/
	rotation.y += angle;
	/*make sure the stored rotation is within 0 and 2PI*/
	while (rotation.x > 2.0f * Utilities::getPI())
	{
		rotation.x -= 2.0f * Utilities::getPI();
	}
	while (rotation.x < 0.0f)
	{
		rotation.x += 2.0f * Utilities::getPI();
	}
}

/**************************************************************************************************************/

/*Rotate the Entity along the Z axis.*/
void Entity::rotateZ(float angle)
{
	/*rotate the model*/
	model->rotateZ(angle);
	/*set the value of rotation*/
	rotation.z += angle;
	/*make sure the stored rotation is within 0 and 2PI*/
	while (rotation.x > 2.0f * Utilities::getPI())
	{
		rotation.x -= 2.0f * Utilities::getPI();
	}
	while (rotation.x < 0.0f)
	{
		rotation.x += 2.0f * Utilities::getPI();
	}
}

/**************************************************************************************************************/

/*Sets the scale of the Entity.*/
void Entity::setScale(float scaleValue)
{
	/*set the scale*/
	this->scaleValue = scaleValue;
	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}

/**************************************************************************************************************/

/*Move the Entity.*/
void Entity::move(glm::vec3 movement)
{
	/*update the position*/
	position += movement;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Move the Entity along the X axis.*/
void Entity::moveX(float movement)
{
	/*update the position*/
	position.x += movement;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Move the Entity along the Y axis.*/
void Entity::moveY(float movement)
{
	/*update the position*/
	position.y += movement;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Move the Entity along the Z axis.*/
void Entity::moveZ(float movement)
{
	/*update the position*/
	position.z += movement;
	/*set the model position*/
	model->setPosition(position);
}

/**************************************************************************************************************/

/*Update the movement speed to the new moveSpeed.*/
void Entity::setMoveSpeed(float moveSpeed)
{
	/*set the move speed*/
	this->moveSpeed = moveSpeed;
}

/**************************************************************************************************************/

/*Get the position.*/
glm::vec3 Entity::getPosition()
{
	/*return the position*/
	return position;
}

/**************************************************************************************************************/

/*Get the orientation.*/
glm::vec3 Entity::getOrientation()
{
	/*return the rotation*/
	return rotation;
}