#pragma once
#ifndef AUXIL_ANIMATION_H_INCLUDED
#define AUXIL_ANIMATION_H_INCLUDED

typedef enum {
	ball_t = 0,
	background_t,
	pad_t,
	road_t,
	ball_creator_t,
	menu_t,
	score_t, 
	waiter_t
}object_type;

typedef enum {
	menu_creating = 0,
	game_proc,
	game_start,
	game_end,
	quit,
	waiting
}scene_type;

using namespace std;

class vec
{
public:
	double x, y, z;

	vec(double x = 0, double y = 0, double z = 0);

	vec& operator +=(const vec &obj);
	vec operator * (double val);
	bool operator == (const vec &obj);
	bool operator != (const vec &obj);

	static vec get_rand(double min, double max);
};

class object
{
public:
	object_type type;
	vec pos;

	object() {}
	virtual ~object() {}
	virtual void render() {}
	virtual void draw() {}
	virtual void keyboard(unsigned char key, int x, int y) {}
	virtual void mouse_button(int button, int state, int mouse_x, int mouse_y) {}
	virtual void mouse_move(int mouse_x, int mouse_y) {}
};

#endif