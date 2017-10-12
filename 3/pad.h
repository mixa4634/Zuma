#pragma once
#ifndef PAD_H_INCLUDED
#define PAD_H_INCLUDED

#include "animation.h"
#include "ball.h"

class pad : public object
{
private:
	unsigned int freq, counter;
	double radius, h;
	vec color;
	ball *new_ball;
	GLUquadricObj *cylinder;
public:
	pad(double radius = 1, vec pos = vec(), vec color = vec(1, 1, 1), unsigned int freq = 1);
	~pad();

	void render(void);
	void draw(void);
	void keyboard(unsigned char key, int x, int y);
};

#endif