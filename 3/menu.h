#pragma once
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <vector>
#include <string>
#include "animation.h"

class menu : public object
{
private:
	int state;
	double height;
	std::vector<std::string> v;
	vec first_color, second_color;
public:
	menu(double height = 1, vec first_color = vec(0, 0, 0), vec second_color = vec(1, 1, 1), vec pos = vec());
	~menu();

	void draw();
	void keyboard(unsigned char key, int x, int y);
};

#endif