#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>

#include "Math.h"

inline float ToRadian(float x)
{
	return x * M_PI / 180.0f;
}

inline float ToDegree(float x)
{
	return x * 180.0f / M_PI;
}

float RandomFloat()
{
	float Max = RAND_MAX;
	return ((float)RANDOM() / Max);
}