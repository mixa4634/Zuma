#pragma once
#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include "gl/glut.h"
#include "auxil_animation.h"

class anim 
{
private:
	int win_id;
	LARGE_INTEGER frequency, start_time; 
	vec pos, dir, up;
	double time;
	static anim instance;

	anim();
	~anim();

	void set_camera(vec &pos, vec &dir, vec &up);
	void clear_stack();
	static void reshape(int w, int h); 
	static void display(void);
	static void idle(void);
	static void keyboard(unsigned char key, int x, int y);
	static void mouse_button(int button, int state, int mouse_x, int mouse_y);
	static void mouse_move(int mouse_x, int mouse_y);
public:
	std::vector<object*> stack; 
	scene_type scene;
	int height, width;
	double total_vel;
		
	void run(void) 
	{
		glutMainLoop();
	}
	void clear_scene(void);
	anim *operator << (object *obj) 
	{
		stack.push_back(obj);
		return this;
	}
	static double get_time(void);
	static anim& get_ref()
	{
		return anim::instance;
	}
};
#endif