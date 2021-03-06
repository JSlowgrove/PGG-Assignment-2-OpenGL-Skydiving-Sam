#include "Player.h"

/**************************************************************************************************************/

/*Constructs a Player Object.*/
Player::Player(Model* model, float scaleValue) : Entity(model, scaleValue)
{
	/*initialise the player speeds*/
	moveSpeed = worldSpeed = 1.0f;
	rotateSpeed = 5.0f;

	/*initialise the player movement*/
	up = down = left = right = rotateDown = false;
	rotateUp = true;

	/*initialise the min angle*/
	minAngle = Utilities::convertAngleToRadian(300.0f);
}

/**************************************************************************************************************/

/*Destructs a Player Object.*/
Player::~Player()
{
	/*delete the pointers*/
	delete model;
}

/**************************************************************************************************************/

/*update the player*/
void Player::update(float dt)
{
	/*movement*/
	updateMovement(dt);

	/*rotation*/
	updateRotation(dt);
		
	/*set the position of the model*/
	model->setPosition(position);

	/*rotate the model*/
	model->rotate(rotation);

	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}

/**************************************************************************************************************/

/*handle inputs*/
void Player::input(SDL_Event &incomingEvent)
{
	/*check the input event type*/
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_w: /*If w is pressed, up is true*/
			up = true;
			break;

		case SDLK_s: /*If s is pressed, down is true*/
			down = true;
			break;

		case SDLK_a: /*If a is pressed, left is true*/
			left = true;
			break;

		case SDLK_d: /*If s is pressed, right is true*/
			right = true;
			break;

		case SDLK_SPACE: /*If space is pressed, roateDown is true*/
			rotateDown = true;
			rotateUp = false;
			break;
		}
		break;

	case SDL_KEYUP:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_w: /*If w is pressed, up is false*/
			up = false;
			break;

		case SDLK_s: /*If s is pressed, down is false*/
			down = false;
			break;

		case SDLK_a: /*If a is pressed, left is false*/
			left = false;
			break;

		case SDLK_d: /*If s is pressed, right is false*/
			right = false;
			break;

		case SDLK_SPACE: /*If space is pressed, roateDown is false*/
			rotateDown = false;
			rotateUp = true;
			break;
		}
		break;
	}
}

/**************************************************************************************************************/

/*Updates the player movement.*/
void Player::updateMovement(float dt)
{
	/*if the up command is true*/
	if (up)
	{
		/*check the player will still be on the screen*/
		if (getPosition().y + (moveSpeed * dt) < 2.0f && getPosition().y + (moveSpeed * dt) > -2.0f)
		{
			/*move the player up*/
			moveY(moveSpeed * dt);
		}
	}

	/*if the down command is true*/
	if (down)
	{
		/*check the player will still be on the screen*/
		if (getPosition().y + (-moveSpeed * dt) < 2.0f && getPosition().y + (-moveSpeed * dt) > -2.0f)
		{
			/*move the player down*/
			moveY(-moveSpeed * dt);
		}
	}

	/*if the left command is true*/
	if (left)
	{
		/*check the player will still be on the screen*/
		if (getPosition().x + (-moveSpeed * dt) < 2.0f && getPosition().x + (-moveSpeed * dt) > -2.0f)
		{
			/*move the player left*/
			moveX(-moveSpeed * dt);
		}
	}

	/*if the right command is true*/
	if (right)
	{
		/*check the player will still be on the screen*/
		if (getPosition().x + (moveSpeed * dt) < 2.0f && getPosition().x + (moveSpeed * dt) > -2.0f)
		{
			/*move the player right*/
			moveX(moveSpeed * dt);
		}
	}
}

/**************************************************************************************************************/

/*Updates the player rotation.*/
void Player::updateRotation(float dt)
{
	/*if the rotate up command is true*/
	if (rotateUp)
	{
		/*rotate the player up using checks*/
		updateRotationCheck(dt, 1.0f);
	}

	/*if the rotate down command is true*/
	if (rotateDown)
	{
		/*rotate the player down using checks*/
		updateRotationCheck(dt, -1.0f);
	}
}

/**************************************************************************************************************/

/*The checks the updated player rotation.*/
void Player::updateRotationCheck(float dt, float direction)
{
	/*creates a variable for the new rotation*/
	float updatedRotation = getOrientation().x + (rotateSpeed * direction * dt);

	/*make sure the stored rotation is within 0 and 2PI*/
	while (updatedRotation > 2.0f * Utilities::getPI())
	{
		updatedRotation -= 2.0f * Utilities::getPI();
	}
	while (updatedRotation < 0.0f)
	{
		updatedRotation += 2.0f * Utilities::getPI();
	}

	/*is the new rotation between the minAngle value and 0*/
	if (updatedRotation > minAngle)
	{
		/*rotate the player*/
		rotateX(rotateSpeed * direction * dt);

		/*update the speedChange*/
		float speedChange = ROTATE_AMOUNT * rotateSpeed * direction * dt;

		/*update speed (minus so it makes the other object move to the camera*/
		worldSpeed -= speedChange;
	}
}

/**************************************************************************************************************/

/*Get the world speed.*/
float Player::getWorldSpeed()
{
	/*return the world speed*/
	return worldSpeed;
}

/**************************************************************************************************************/

/*Sets the user commands to false.*/
void Player::resetCommands()
{
	/*set to false*/
	up = down = left = right = rotateDown = false;
	/*set to true*/
	rotateUp = true;
}