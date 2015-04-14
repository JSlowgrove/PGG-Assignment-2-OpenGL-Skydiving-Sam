#pragma once

#include <glm.hpp>

/**
@brief A namespace to contain utility functions.
@author Jamie Slowgrove
*/
namespace Utilities
{
/**A definition of pi*/
#define PI 3.141596f

	/**
	Getter # Gets the value for PI.
	@returns float The value for PI.
	*/
	float getPI();

	/**
	Converts the angle to a radian.
	@param float The angle to convert.
	@returns float The converted radian.
	*/
	float convertAngleToRadian(float angle);	
}