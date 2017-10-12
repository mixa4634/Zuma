#include "ball.h"
#include "road.h"
#include "score.h"

ball::ball(double radius,vec pos, vec vel, vec color, bool collision_detection) :
	radius(radius),
	vel(vel),
	color(color),
	collision_detection(collision_detection)
{
	type = ball_t;
	this->pos = pos;
}

ball::~ball()
{
	if (anim::get_ref().scene == game_proc && collision_detection == true)
		score::get_inst().decrease_val(0.1);
}

void ball::render()
{
	if (collision_detection == true)
		road::get_inst().collision_detection(this);
	pos += vel * anim::get_ref().total_vel;
}

void ball::draw()
{
	glColor3d(color.x, color.y, color.z);
	glPushMatrix();
	glTranslated(pos.x, pos.y, pos.z);
	glutSolidSphere(radius, 30, 30);
	glPopMatrix();
}

void ball::set_pos(double x, double y, double z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void ball::set_vel(double x, double y, double z)
{
	vel.x = x;
	vel.y = y;
	vel.z = z;
}

void ball::set_vel(const vec & obj)
{
	vel = obj;
}

double ball::get_rad()
{
	return radius;
}

vec ball::get_next_color()
{
	int c = rand() % white;

	switch (c)
	{
	case blue:
		return vec(85.0 / 255, 207.0 / 255, 214.0 / 255);
	case green:
		return vec(128.0 / 255, 154.0 / 255, 65.0 / 255);
	case red:
		return vec(148.0 / 255, 23.0 / 255, 15.0 / 255);
	case orange:
		return vec(254.0 / 255, 126.0 / 255, 15.0 / 255);
	case pink:
		return vec(254.0 / 255, 76.0 / 255, 74.0 / 255);
	case yellow:
		return vec(255.0 / 255, 212.0 / 255, 0.0 / 255);
	default:
		return vec(0, 0, 0);
	}
}