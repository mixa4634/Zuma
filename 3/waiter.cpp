#include "waiter.h"

using namespace std;

waiter::waiter(scene_type s, string str, vec pos, vec color) :
	s(s),
	color(color),
	str(str)
{
	this->pos = pos;
	type = waiter_t;
}

void waiter::draw()
{
	glColor3d(color.x, color.y, color.z);
	glRasterPos3d(pos.x, pos.y, pos.z);
	for (int i = 0; i < (int)str.length(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)str[i]);
}

void waiter::keyboard(unsigned char key, int x, int y)
{
	anim::get_ref().scene = s;
}