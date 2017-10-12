#pragma once
#ifndef BALL_CREATOR_H_INCLUDED
#define BALL_CREATOR_H_INCLUDED 

#include "animation.h"

class ball_creator : public object
{
private:
	unsigned int base_num, curr_num, counter, 
		r_freq, r_counter;
	double radius;
public:
	ball_creator(unsigned int num = 2, double radius = 1, unsigned int r_freq = 1);
	~ball_creator();

	void render();
};

#endif