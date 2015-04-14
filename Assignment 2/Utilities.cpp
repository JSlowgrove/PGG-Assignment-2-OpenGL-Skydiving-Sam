#include "Utilities.h"

/*A namespace to contain utility functions.*/
namespace Utilities
{
	/*Get the value for PI*/
	float getPI()
	{
		/*return the value for PI*/
		return PI;
	}

	/**************************************************************************************************************/

	/*Converts the angle to a radian.*/
	float convertAngleToRadian(float angle)
	{
		/*return the radian*/
		return (angle * PI / 180.0f);
	}
}