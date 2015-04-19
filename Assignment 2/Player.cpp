#include "Player.h"

/**************************************************************************************************************/

/*Constructs a Player Object.*/
Player::Player(std::shared_ptr<Model> model, float scaleValue) : Entity(model, scaleValue)
{
	/*initialise the player speeds*/
	moveSpeed = 1.0f;
	rotateSpeed = 1.0f;

	/*initialise the camera movement*/
	up = down = left = right = rotateUp = rotateDown = false;
}

/**************************************************************************************************************/

/*Destructs a Player Object.*/
Player::~Player()
{
}

/**************************************************************************************************************/

/*update the player*/
void Player::update(float dt)
{
	/*movement*/
	if (up)
	{
		/*check the player will still be on the screen*/
		if (getPosition().y + (moveSpeed * dt) < 0.9f && getPosition().y + (moveSpeed * dt) > -1.6f)
		{
			moveY(moveSpeed * dt);
		}
	}
	if (down)
	{
		/*check the player will still be on the screen*/
		if (getPosition().y + (-moveSpeed * dt) < 0.9f && getPosition().y + (-moveSpeed * dt) > -1.6f)
		{
			moveY(-moveSpeed * dt);
		}
	}
	if (left)
	{
		/*check the player will still be on the screen*/
		if (getPosition().x + (-moveSpeed * dt) < 1.7f && getPosition().x + (-moveSpeed * dt) > -1.7f)
		{
			moveX(-moveSpeed * dt);
		}
	}
	if (right)
	{
		/*check the player will still be on the screen*/
		if (getPosition().x + (moveSpeed * dt) < 1.7f && getPosition().x + (moveSpeed * dt) > -1.7f)
		{
			moveX(moveSpeed * dt);
		}
	}

	/*rotation*/
	if (rotateUp)
	{
		rotateX(rotateSpeed * dt);
	}
	if (rotateDown)
	{
		rotateX(-rotateSpeed * dt);
	}

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
			break;
		}
		break;
	}
}