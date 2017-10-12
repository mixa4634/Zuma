#pragma once
#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include "animation.h"

class score : public object
{
private:
	double val;
	vec color;
	static score *instance;
public:
	score(vec pos = vec(), vec color = vec(1, 1, 1));
	~score();

	void draw();
	double get_val();
	void set_val(double val);
	void increase_val(double val);
	void decrease_val(double val);

	static score& get_inst();
};

#endif