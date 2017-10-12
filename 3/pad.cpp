#include "pad.h"

pad::pad(double radius, vec pos, vec color, unsigned int freq) :
	new_ball(nullptr), 
	radius(radius), 
	color(color),
	freq(freq)
{
	cylinder = gluNewQuadric();
	this->pos = pos;
	type = pad_t;
	h = 4;
	counter = 0;
}

pad::~pad()
{
	delete new_ball;
}

void pad::render(void)
{
	if (new_ball == nullptr && counter > freq)
	{
		new_ball = new ball(radius, vec(0, 0, 0), vec(0, 0, 0), ball::get_next_color(), true);
	}
	if (counter <= freq)
		++counter;
}

void pad::draw(void)
{
	double r = 1.3;

	glColor3d(color.x, color.y, color.z);
	glPushMatrix();
	glTranslated(pos.x, pos.y, pos.z);
	glRotated(90, -1, 0, 0);
	gluCylinder(cylinder, r * radius, radius, h * radius, 100, 100);
	glTranslated(0, 0, h * radius);
	if (new_ball != nullptr)
		new_ball->draw();
	else
		gluDisk(cylinder, 0, 1.01 * radius, 30, 30);
	glPopMatrix();
}

void pad::keyboard(unsigned char key, int x, int y)
{
	double vel_p = 1, vel_b = 3;

	switch (key)
	{
	case 'a':
		pos.x -= radius / vel_p;
		break;
	case 'd':
		pos.x += radius / vel_p;
		break;
	case ' ':
		if (new_ball != nullptr)
		{
			new_ball->set_pos(pos.x, pos.y + h * radius, pos.z);
			new_ball->set_vel(0, radius / vel_b, 0);
			anim::get_ref() << new_ball;
			new_ball = nullptr;
			counter = 0;
		}
		break;
	}   
}