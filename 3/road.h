#pragma once
#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

#include <vector>
#include <functional>
#include "animation.h"
#include "point.h"
#include "ball_creator.h"

class road : public object
{
private:
	int freq;
	double speed, step_counter, height, scale;
	std::vector<point> v;
	vec color;
	static road *instance;

	double integr_len(std::function<double(double)> f, double a, double b, double n = 1000);
	double integr_seg(std::function<double(double)> f, double x_prev, double len, double step);
	void scale_func(vec area_p_1, vec area_p_2, double scale = 1);
	void boom_func(int i, int step, double k, vec color);
	void insert_func(int i, ball *b);
	int insert_pos_search(int i, int &num, bool &direction);
public:
	road(
		double speed = 1,
		double height = 0, 
		vec color = vec(1, 1, 1), 
		std::function<double(double)> f = [](double x) { return x; }, 
		int points_num = 100, 
		vec area_p_1 = vec(-1, 1, 0), 
		vec area_p_2 = vec(1, -1, 0), 
		int freq = 1,
		double scale = 1);
	~road();

	void render();
	void draw();
	void collision_detection(ball *b);

	static road& get_inst();
	static road* get_p();

	friend ball_creator;
};

#endif