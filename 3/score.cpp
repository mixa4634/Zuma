#include <string>
#include "score.h"

using namespace std;

score *score::instance;

score::score(vec pos, vec color) :
	color(color)
{
	this->pos = pos;
	val = 0;
	instance = this;
	type = score_t;
}

score::~score()
{
}

void score::draw()
{
	string s("Score: " + to_string(val));
	size_t size = s.find("00");

	s.resize(size + 1);
	glColor3d(color.x, color.y, color.z);
	glRasterPos3d(pos.x, pos.y, pos.z);
	for (int i = 0; i < (int)s.length(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)s[i]);
}

double score::get_val()
{
	return instance->val;
}

void score::set_val(double val)
{
	instance->val = val;
}

void score::increase_val(double val)
{
	instance->val += val;
}

void score::decrease_val(double val)
{
	instance->val -= val;
}

score & score::get_inst()
{
	return *instance;
}