#include "Camera.h"

/**************************************************************************************************************/

/*Constructs a Camera object.*/
Camera::Camera()
{
	/*initialise the projection matrix for the camera (camera lense)*/
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	/*initialise the view matrix for the camera*/
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2.5f));
}

/**************************************************************************************************************/

/*Destructs an Camera object.*/
Camera::~Camera()
{
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
	view = glm::rotate(view, rotation.x, glm::vec3(1, 0, 0));
	view = glm::rotate(view, rotation.y, glm::vec3(0, 1, 0));
	view = glm::rotate(view, rotation.z, glm::vec3(0, 0, 1));
}

/**************************************************************************************************************/

/*Rotate the Camera along the X axis.*/
void Camera::rotateCameraAlongX(float rotationX)
{
	/*Rotates the Camera along the X axis*/
	view = glm::rotate(view, rotationX, glm::vec3(1, 0, 0));
}

/**************************************************************************************************************/

/*Rotate the Camera along the Y axis.*/
void Camera::rotateCameraAlongY(float rotationY)
{
	/*Rotates the Camera along the Y axis*/
	view = glm::rotate(view, rotationY, glm::vec3(0, 1, 0));
}

/**************************************************************************************************************/

/*Rotate the Camera along the Z axis.*/
void Camera::rotateCameraAlongZ(float rotationZ)
{
	/*Rotates the Camera along the Z axis*/
	view = glm::rotate(view, rotationZ, glm::vec3(0, 0, 1));
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