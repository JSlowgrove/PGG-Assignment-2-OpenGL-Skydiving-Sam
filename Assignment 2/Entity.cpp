#include "Entity.h"

/**************************************************************************************************************/

/*Constructs a Entity Object.*/
Entity::Entity(std::string vertexShaderFileLocation, std::string fragmentShaderFileLocation, std::string objFileLocation)
{
	/*initialise the model*/
	model = new Model(vertexShaderFileLocation, fragmentShaderFileLocation, objFileLocation);
}

/**************************************************************************************************************/

/*Destructs a Entity Object.*/
Entity::~Entity()
{
}

/**************************************************************************************************************/

void Entity::update(float deltaTs)
{
	// update the rotation angle of our cube
	rotation.y += deltaTs * 0.5f;
	while (rotation.y > (3.14159265358979323846 * 2.0))
	{
		rotation.y -= (float)(3.14159265358979323846 * 2.0);
	}
	
	// Build the model matrix!
	// First we start with an identity matrix
	// This is created with the command: glm::mat4(1.0f)
	// Next, we translate this matrix according to the object's _position vector:
	model->setPosition(position);
	// Next, we rotate this matrix in the y-axis by the object's y-rotation:
	model->rotateY(rotation.y);
	// Scale the matrix to scale the object:
	model->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	// And there we go, model matrix is ready!
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
}