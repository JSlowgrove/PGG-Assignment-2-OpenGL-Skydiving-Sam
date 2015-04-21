#include "Ring.h"

/**************************************************************************************************************/

/*Constructs a Ring Object.*/
Ring::Ring(Model* model, float scaleValue, int AI) : Entity(model, scaleValue)
{
	/*initialise the move speeds of the ring*/
	moveSpeed = moveSpeedAI = 1.0f;
	scaleSpeedAI = 0.15f;
	
	/*store the AI type of the Ring.*/
	this->AI = AI;
	
	/*initialise the circle angle*/
	circleAngle = 0.0f;
	
	/*initialise the radius that the ring will follow (between 0.0f and 1.5f)*/
	circleRadius = (float)((rand() % 16)) * 0.1f;

	/*initialise the XY directions*/
	directionXY = glm::vec2(1.0f, 1.0f);

	/*initialise the scale direction*/
	scaleDirection = 1.0f;
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
	/*apply the AI of the ring*/
	switch(AI)
	{
		/*if AI type is 0*/
		case 0:		
			/*apply type 0 AI*/
			typeZeroAI(dt);
			break;
			
		/*if AI type is 1*/
		case 1:		
			/*apply type 1 AI*/
			typeOneAI(dt);
			break;
			
		/*if AI type is 2*/
		case 2:		
			/*apply type 2 AI*/
			typeTwoAI(dt);
			break;
			
		/*if AI type is 3*/
		case 3:		
			/*apply type 3 AI*/
			typeThreeAI(dt);
			break;
			
		/*if AI type is 4*/
		case 4:		
			/*apply type 4 AI*/
			typeFourAI(dt);
			break;
	}
		
	/*move the ring towards the camera*/
	moveZ(moveSpeed * dt);

	/*set the position of the model*/
	model->setPosition(position);

	/*rotate the model*/
	model->rotate(rotation);

	/*scale the model*/
	model->scale(glm::vec3(scaleValue, scaleValue, scaleValue));
}

/**************************************************************************************************************/

/*Apply the action of AI type 0.*/
void Ring::typeZeroAI(float dt)
{
	/*The ring does nothing.*/
}

/**************************************************************************************************************/

/*Apply the action of AI type 1.*/
void Ring::typeOneAI(float dt)
{
	/*if the x position is less than -1.5f*/
	if (position.x < -1.5f)
	{
		/*set the x direction to right*/
		directionXY.x = 1.0f;
	}
	/*if the x position is greater than 1.5f*/
	if (position.x > 1.5f)
	{
		/*set the x direction to left*/
		directionXY.x = -1.0f;
	}
	/*move the ring*/
	moveX(directionXY.x * moveSpeedAI * dt);
}

/**************************************************************************************************************/

/*Apply the action of AI type 2.*/
void Ring::typeTwoAI(float dt)
{
	/*if the y position is less than -1.5f*/
	if (position.y < -1.5f)
	{
		/*set the y direction to up*/
		directionXY.y = 1.0f;
	}
	/*if the y position is greater than 1.5f*/
	if (position.y > 1.5f)
	{
		/*set the y direction to down*/
		directionXY.y= -1.0f;
	}
	/*move the ring*/
	moveY(directionXY.y * moveSpeedAI * dt);
}

/**************************************************************************************************************/

/*Apply the action of AI type 3.*/
void Ring::typeThreeAI(float dt)
{
	/*if the scale is less than 0.08f*/
	if (scaleValue < 0.08f)
	{
		/*set the scale direction to up*/
		scaleDirection = 1.0f;
	}
	/*if the scale is greater than 0.25f*/
	if (scaleValue > 0.25f)
	{
		/*set the scale direction to down*/
		scaleDirection = -1.0f;
	}
	/*update the scale*/
	scaleValue += scaleDirection * scaleSpeedAI * dt;
}

/**************************************************************************************************************/

/*Apply the action of AI type 4.*/
void Ring::typeFourAI(float dt)
{
	/*set the centre point of the circle the ring will follow*/
	glm::vec2 centrePosition = glm::vec2(0.0f, 0.0f);
	
	/*increase the angle on this circle that the ring will be*/
	circleAngle += moveSpeedAI * dt;
	/*make sure this is and angle between 0 and 360*/
	while (circleAngle > 360.0f)
	{
		circleAngle -= 360.0f;
	}
	
	/*work out the new position of the ring*/
	position.x  = centrePosition.x + sin(circleAngle) * circleRadius;
	position.y  = centrePosition.y + cos(circleAngle) * circleRadius;
}