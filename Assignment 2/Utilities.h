#pragma once

#include <glm.hpp>

/**
@brief A namespace to contain utility functions.
@author Jamie Slowgrove
*/
namespace Utilities
{
/**A definition of PI*/
#define PI 3.141596f

	/**
	Getter # Gets the value for PI.
	@returns The value for PI.
	*/
	float getPI();

	/**
	Converts the angle to a radian.
	@param angle The angle to convert.
	@returns The converted radian.
	*/
	float convertAngleToRadian(float angle);	
}