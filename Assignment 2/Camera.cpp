#include "Camera.h"

/**************************************************************************************************************/

/*Constructs a Camera object.*/
Camera::Camera()
{
	/*initialise the projection matrix for the camera (camera lense)*/
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 200.0f);
	/*initialise the view matrix for the camera*/
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	/*initialise the orientation*/
	orientation = glm::vec3(0.0f, 0.0f, 0.0f);

	/*initialise the camera movement*/
	up = down = left = right = forwards = backwards = rotateRight = rotateLeft =
		rotateUp = rotateDown = rollLeft = rollRight = false;

	/*initialise the mouse position*/
	mouse = glm::vec2(0.0f, 0.0f);

	/*initialise the camera speeds*/
	moveSpeed = 1.0f;
	rotateSpeed = 1.0f;
}

/**************************************************************************************************************/

/*Destructs an Camera object.*/
Camera::~Camera()
{
}

/**************************************************************************************************************/

/*handle inputs*/
void Camera::input(SDL_Event &incomingEvent)
{
	/*update the mouse position*/
	mouse.x = ((float)incomingEvent.motion.x);
	mouse.y = ((float)incomingEvent.motion.y);

	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_w: /*If w is pressed, forwards is true*/
			forwards = true;
			break;

		case SDLK_s: /*If s is pressed, backwards is true*/
			backwards = true;
			break;

		case SDLK_a: /*If a is pressed, left is true*/
			left = true;
			break;

		case SDLK_d: /*If s is pressed, right is true*/
			right = true;
			break;

		case SDLK_UP: /*If up is pressed, rotateUp is true*/
			rotateUp = true;
			break;

		case SDLK_DOWN: /*If down is pressed, rotateDown is true*/
			rotateDown = true;
			break;

		case SDLK_LEFT: /*If left is pressed, rotateLeft is true*/
			rotateLeft = true;
			break;

		case SDLK_RIGHT: /*If right is pressed, rotateRight is true*/
			rotateRight = true;
			break;

		case SDLK_q: /*If q is pressed, up is true*/
			up = true;
			break;

		case SDLK_e: /*If e is pressed, down is true*/
			down = true;
			break;
		}
		break;

	case SDL_KEYUP:

		switch (incomingEvent.key.keysym.sym)
		{

		case SDLK_w: /*If w is released, forwards is false*/
			forwards = false;
			break;

		case SDLK_s: /*If s is released, backwards is false*/
			backwards = false;
			break;

		case SDLK_a: /*If a is released, left is false*/
			left = false;
			break;

		case SDLK_d: /*If d is released, right is false*/
			right = false;
			break;

		case SDLK_UP: /*If up is released, rotateUp is false*/
			rotateUp = false;
			break;

		case SDLK_DOWN: /*If down is released, rotateDown is false*/
			rotateDown = false;
			break;

		case SDLK_LEFT: /*If left is released, rotateLeft is false*/
			rotateLeft = false;
			break;

		case SDLK_RIGHT: /*If right is released, rotateRight is false*/
			rotateRight = false;
			break;

		case SDLK_q: /*If q is pressed, up is false*/
			up = false;
			break;

		case SDLK_e: /*If e is pressed, down is false*/
			down = false;
			break;
		}
		break;

	case SDL_MOUSEBUTTONDOWN:

		/*If left mouse is pressed, rollLeft is true*/
		if (incomingEvent.button.button == SDL_BUTTON_LEFT)
		{
			rollLeft = true;
		}

		/*If right mouse is pressed, rollRight is true*/
		if (incomingEvent.button.button == SDL_BUTTON_RIGHT)
		{
			rollRight = true;
		}

		break;

	case SDL_MOUSEBUTTONUP:

		/*If left mouse is released, rollLeft is false*/
		if (incomingEvent.button.button == SDL_BUTTON_LEFT)
		{
			rollLeft = false;
		}

		/*If right mouse is released, rollRight is false*/
		if (incomingEvent.button.button == SDL_BUTTON_RIGHT)
		{
			rollRight = false;
		}

		break;
	}
}

/**************************************************************************************************************/

/*updates the camera*/
void Camera::update(float dt)
{
	/*camera movement*/
	if (up)
	{
		moveCameraAlongY(-moveSpeed * dt);
	}
	if (down)
	{
		moveCameraAlongY(moveSpeed * dt);
	}
	if (forwards)
	{
		moveCameraAlongZ(-moveSpeed * dt);
	}
	if (backwards)
	{
		moveCameraAlongZ(moveSpeed * dt);
	}
	if (left)
	{
		moveCameraAlongX(-moveSpeed * dt);
	}
	if (right)
	{
		moveCameraAlongX(moveSpeed * dt);
	}

	/*camera rotation*/
	if (rotateUp)
	{
		rotateCameraAlongX(-rotateSpeed * dt);
	}
	if (rotateDown)
	{
		rotateCameraAlongX(rotateSpeed * dt);
	}
	if (rotateRight)
	{
		rotateCameraAlongY(rotateSpeed * dt);
	}
	if (rotateLeft)
	{
		rotateCameraAlongY(-rotateSpeed * dt);
	}
	if (rollRight)
	{
		rotateCameraAlongZ(rotateSpeed * dt);
	}
	if (rollLeft)
	{
		rotateCameraAlongZ(-rotateSpeed * dt);
	}
}

/**************************************************************************************************************/

/*Moves the Camera using the translation.*/
void Camera::moveCamera(glm::vec3 translation)
{
	/*Create a viewing matrix for the camera 'Camera orientation'. 
	The translation is inverted to work with OpenGL*/
	view = glm::translate(view, -translation);
}

/**************************************************************************************************************/

/*Moves the Camera along the X axis.*/
void Camera::moveCameraAlongX(float translateX)
{
	/*Create a viewing matrix for the camera 'Camera orientation'.
	The translation is inverted to work with OpenGL*/
	view = glm::translate(view, glm::vec3(-translateX, 0.0f, 0.0f));
}

/**************************************************************************************************************/

/*Moves the Camera along the Y axis.*/
void Camera::moveCameraAlongY(float translateY)
{
	/*Create a viewing matrix for the camera 'Camera orientation'.
	The translation is inverted to work with OpenGL*/
	view = glm::translate(view, glm::vec3(0.0f, -translateY, 0.0f));
}

/**************************************************************************************************************/

/*Moves the Camera along the Z axis.*/
void Camera::moveCameraAlongZ(float translateZ)
{
	/*Create a viewing matrix for the camera 'Camera orientation'.
	The translation is inverted to work with OpenGL*/
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -translateZ));
}

/**************************************************************************************************************/

/*Rotates the Camera using the rotation.*/
void Camera::rotateCamera(glm::vec3 rotation)
{
	/*Rotates the Camera*/
	view = glm::rotate(view, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	/*update the stored orientation*/
	orientation = rotation;

	
}

/**************************************************************************************************************/

/*Rotate the Camera along the X axis.*/
void Camera::rotateCameraAlongX(float rotationX)
{
	/*Rotates the Camera along the X axis*/
	view = glm::rotate(view, rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
	/*update the stored orientation*/
	orientation.x = rotationX;
}

/**************************************************************************************************************/

/*Rotate the Camera along the Y axis.*/
void Camera::rotateCameraAlongY(float rotationY)
{
	/*Rotates the Camera along the Y axis*/
	view = glm::rotate(view, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
	/*update the stored orientation*/
	orientation.y = rotationY;
}

/**************************************************************************************************************/

/*Rotate the Camera along the Z axis.*/
void Camera::rotateCameraAlongZ(float rotationZ)
{
	/*Rotates the Camera along the Z axis*/
	view = glm::rotate(view, rotationZ, glm::vec3(0.0f, 0.0f, 1.0f));
	/*update the stored orientation*/
	orientation.z = rotationZ;
}

/**************************************************************************************************************/

/*Returns the Camera view matrix.*/
glm::mat4 Camera::getView()
{
	/*return the Camera view matrix*/
	return view;
}

/**************************************************************************************************************/

/*Returns the Camera projection matrix.*/
glm::mat4 Camera::getProjection()
{
	/*return the Camera projection matrix*/
	return projection;
}

/**************************************************************************************************************/

/*Returns the Camera orientation.*/
glm::vec3 Camera::getOrientation()
{
	/*return the Camera orientation*/
	return orientation;
}

/**************************************************************************************************************/

/*Sets the position of the Camera.*/
void Camera::setPosition(glm::vec3 position)
{
	/*set the position*/
	view = glm::translate(glm::mat4(1.0f), position);
}