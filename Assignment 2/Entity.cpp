#include "Entity.h"

/**************************************************************************************************************/

/*Constructs a Entity Object.*/
Entity::Entity(std::shared_ptr<Model> model, float scaleValue)
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

void Entity::update(float deltaTs)
{
	/*set the position of the model*/
	model->setPosition(position);

	/*rotate the model*/
	model->rotate(rotation);

	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
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
}

/**************************************************************************************************************/

/*Rotate the Entity along the Y axis.*/
void Entity::rotateY(float angle)
{
	/*rotate the model*/
	model->rotateY(angle);
	/*set the value of rotation*/
	rotation.y += angle;
}

/**************************************************************************************************************/

/*Rotate the Entity along the Z axis.*/
void Entity::rotateZ(float angle)
{
	/*rotate the model*/
	model->rotateZ(angle);
	/*set the value of rotation*/
	rotation.z += angle;
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