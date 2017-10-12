#include <cmath>
#include "auxil_animation.h"

vec::vec(double x, double y, double z) :
	x(x),
	y(y),
	z(z)
{
}

vec & vec::operator+=(const vec & obj)
{
	x += obj.x;
	y += obj.y;
	z += obj.z;

	return *this;
}

vec vec::operator*(double val)
{
	return vec(x * val, y * val, z * val);
}

bool vec::operator==(const vec & obj)
{
	return (x == obj.x) && (y == obj.y) && (z == obj.z);
}

bool vec::operator!=(const vec & obj)
{
	return (x != obj.x) || (y != obj.y) || (z != obj.z);
}

vec vec::get_rand(double min, double max)
{
	int num = 100;
	double 
		x_1 = (rand() % num) / (double)num,
		x_2 = (rand() % num) / (double)num;
	return vec(min * x_1 + (1 - x_1) * max, min * x_2 + (1 - x_2) * max, 0);

}