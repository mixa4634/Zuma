#pragma once
#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "animation.h"

enum colours
{
	blue = 0,
	green,
	red,
	orange,
	pink,
	yellow,
	white,
	black
};

class ball : public object
{
private:
	double radius;
	vec vel;
public:
	bool collision_detection;
	vec color;

	ball(double radius = 0, vec pos = vec(), vec vel = vec(), vec color = vec(1, 1, 1), bool collision_detection = false);
	~ball();

	void render();
	void draw();

	void set_pos(double x = 0, double y = 0, double z = 0);
	void set_vel(double x = 0, double y = 0, double z = 0);
	void set_vel(const vec &obj);

	double get_rad();

	static vec get_next_color();
};

#endif