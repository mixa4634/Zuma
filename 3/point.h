#pragma once
#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "ball.h"

class point
{
public:
	double x, y;
	ball *b;

	point(double x = 0, double y = 0, ball *b = nullptr);
	~point();
};

#endif 