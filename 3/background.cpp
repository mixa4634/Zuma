#include "background.h"

background::background(double height, vec color) :
	height(height),
	color(color)
{
	pos_1.x = -anim::get_ref().width / (double)anim::get_ref().height;
	pos_1.y = -1;
	pos_2.x = anim::get_ref().width / (double)anim::get_ref().height;
	pos_2.y = 1;
	type = background_t;
}

background::~background()
{
}

void background::draw()
{
	glPushMatrix();
	glTranslated(0, 0, height);
	glColor3d(color.x, color.y, color.z);
	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glVertex3d(pos_1.x, pos_1.y, height);
	glNormal3d(0, 0, 1);
	glVertex3d(pos_1.x, pos_2.y, height);
	glNormal3d(0, 0, 1);
	glVertex3d(pos_2.x, pos_2.y, height);
	glNormal3d(0, 0, 1);
	glVertex3d(pos_2.x, pos_1.y, height);
	glEnd();
	glPopMatrix();
}