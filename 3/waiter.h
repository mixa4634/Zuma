#pragma once
#ifndef WAITER_H_INCLUDED
#define WAITER_H_INCLUDED

#include <string>
#include "animation.h"

class waiter : public object
{
private:
	std::string str;
	scene_type s;
	vec color;
public:
	waiter(scene_type s = menu_creating, std::string str = "", vec pos = vec(), vec color = vec(1, 1, 1));
	
	void  draw();
	void keyboard(unsigned char key, int x, int y);
};

#endif