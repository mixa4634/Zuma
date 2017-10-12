#include "menu.h"

menu::menu(double height, vec first_color, vec second_color, vec pos) :
	first_color(first_color),
	second_color(second_color),
	height(height)
{
	this->pos = pos;
	state = 0;
	v.push_back("New game");
	v.push_back("Exit");
	type = menu_t;
}

menu::~menu()
{
}

void menu::draw()
{
	
	for (int i = 0; i < (int)v.size(); ++i)
	{
		if(i != state)
			glColor3d(first_color.x, first_color.y, first_color.z);
		else
			glColor3d(second_color.x, second_color.y, second_color.z);
		glRasterPos3d(pos.x, pos.y - i * height, pos.z);
		for (int j = 0; j < (int)v[i].length(); ++j)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)v[i][j]);
	}
}

void menu::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		--state;
		state += v.size();
		state %= v.size();
		break;
	case 's':
		++state;
		state %= v.size();
		break;
	case 13:
		switch (state)
		{
		case 0:
			anim::get_ref().scene = game_start;
			break;
		case 1:
			anim::get_ref().scene = quit;
			break;

		}
		break;
	}
}