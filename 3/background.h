#pragma once
#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "animation.h"

class background : public object
{
private:
	double height;
	vec color, pos_1, pos_2;
public:
	background(double height = 0, vec color = vec(1, 1, 1));
	~background();

	void draw();
};

#endif