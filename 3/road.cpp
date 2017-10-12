#include <cmath>
#include "road.h"
#include "score.h"

using namespace std;

road* road::instance;

double road::integr_len(function<double(double)> f, double a, double b, double n)
{
	double h = (b - a) / (n - 1), der = 0, x_1 = a, x_2 = a + h, res = 0;

	der = (f(x_2) - f(x_1)) / h;
	x_1 = x_2;
	x_2 += h;
	res += sqrt(1 + der * der) / 2;
	for (int i = 1; i < n - 2; ++i)
	{
		der = (f(x_2) - f(x_1)) / h;
		res += sqrt(1 + der * der);
		x_1 = x_2;
		x_2 += h;
	}
	der = (f(x_2) - f(x_1)) / h;
	res += sqrt(1 + der * der) / 2;

	return res * h;
}

double road::integr_seg(std::function<double(double)> f, double x_prev, double len, double step)
{
	double der = 0, x_1 = x_prev, x_2 = x_prev + step, res = 0;

	der = (f(x_2) - f(x_1)) / step;
	x_1 = x_2;
	x_2 += step;
	res += sqrt(1 + der * der) / 2 * step;
	while(res < len)
	{
		der = (f(x_2) - f(x_1)) / step;
		res += sqrt(1 + der * der) / 2 * step;
		if (res < len)
		{
			res += sqrt(1 + der * der) / 2 * step;
			x_1 = x_2;
			x_2 += step;
		}
	}

	return x_2;
}

void road::scale_func(vec area_p_1, vec area_p_2, double scale)
{
	double max = v[0].y, min = max;

	for (vector<point>::iterator i = v.begin() + 1; i != v.end(); i = i + 1)
		if (i->y > max)
			max = i->y;
		else
			if (i->y < min)
				min = i->y;
	for (vector<point>::iterator i = v.begin(); i != v.end(); i = i + 1)
	{
		i->y = (area_p_1.y * (i->y - min) / (max - min) + area_p_2.y * (1 - (i->y - min) / (max - min))) * scale;
		i->x *= scale;
	}
}

void road::boom_func(int i, int step, double k, vec color)
{
	int count = 1;

	i += step;
	while (i >= 0 && i < (int)v.size() && v[i].b != nullptr && v[i].b->color == color)
	{
		v[i].b->set_vel(vec::get_rand(-k, k));
		v[i].b->set_pos(v[i].x, v[i].y, 0);
		v[i].b = nullptr;
		i += step;
		score::get_inst().increase_val(count);
		++count;
	}
}

void road::insert_func(int i, ball * b)
{
	int num;
	bool direction;

	insert_pos_search(i, num, direction);
	if (num != 0)
	{
		for (int k = num; k > 1; k--)
			v[i + k * freq * (direction == 1 ? 1 : -1)].b = v[i + (k - 1) * freq * (direction == 1 ? 1 : -1)].b;
		v[i + freq * (direction == 1 ? 1 : -1)].b = b;
	}
	else
		anim::get_ref().scene = game_end;
}

int road::insert_pos_search(int i, int & num, bool &direction)
{
	int j;

	num = 0;
	direction = 1;
	for (j = 1; i + j * freq < (int)v.size() && v[i + j * freq].b != nullptr; ++j);
	if (i + j * freq < (int)v.size())
		num = j;
	for (j = 1; i - j * freq >= 0 && v[i - j * freq].b != nullptr; ++j);
	if (i - j * freq >= 0 && j < num)
	{
		num = j;
		direction = 0;
	}
	if (num == 0)
		return 1;

	return 0;
}

road::road(double speed, double height, vec color, function<double(double)> f, int points_num, vec area_p_1, vec area_p_2, int freq, double scale) :
	color(color),
	height(height),
	speed(speed),
	freq(freq),
	scale(scale)
{
	if (area_p_1.x > area_p_2.x)
		swap(area_p_1, area_p_2);
	double 
		len = integr_len(f, area_p_1.x, area_p_2.x, points_num),
		x_prev = area_p_1.x;
	
	this->freq /= ceil(1 / speed);
	type = road_t;
	step_counter = 0;
	points_num -= 2;
	v.push_back(point(area_p_1.x, f(area_p_1.x)));
	for (int i = 0; i < points_num; ++i)
	{
		double x = integr_seg(f, x_prev, len / points_num, (area_p_2.x - area_p_1.x) / points_num / points_num);

		v.push_back(point(x, f(x)));
		x_prev = x;
	}
	v.push_back(point(area_p_2.x, f(area_p_2.x)));
	scale_func(area_p_1, area_p_2, scale);
	instance = this;
}

road::~road()
{
}

road & road::get_inst()
{
	return *instance;
}

road * road::get_p()
{
	return instance;
}

void road::render()
{
	if(v[v.size() - 1].b != nullptr)
		anim::get_ref().scene = game_end;
	else
	{
		if (step_counter >= 1)
		{
			for (vector<point>::iterator i = v.end() - 1; i != v.begin(); i = i - 1)
				i->b = (i - 1)->b;
			v[0].b = nullptr;
			step_counter = speed;
		}
		else
			step_counter += speed;
	}
}

void road::draw()
{
	glColor3d(color.x, color.y, color.z);
	glLineWidth(25);
	glPushMatrix();
	glTranslated(0, 0, height);
	glBegin(GL_LINE_STRIP);
	for (vector<point>::iterator i = v.begin(); i != v.end(); i = i + 1)
	{
		glNormal3i(0, 0, 1);
		glVertex3d(i->x, i->y, 0);
		if(i->b != nullptr)
			i->b->set_pos(i->x, i->y, 0);
	}
	glEnd();
	glPopMatrix();
}

void road::collision_detection(ball * b)
{
	double min_val = 1e10;
	int min_pos = -1;

	for (int i = 0; i < (int)v.size(); ++i)
		if (v[i].b != nullptr)
		{
			double val = sqrt((v[i].x - b->pos.x) * (v[i].x - b->pos.x) + (v[i].y - b->pos.y) * (v[i].y - b->pos.y));

			if (val < min_val)
			{
				min_pos = i;
				min_val = val;
			}
		}
	if (min_pos == -1)
		return;

	bool backward = (min_pos - freq >= 0 && v[min_pos - freq].b != nullptr && v[min_pos - freq].b->color == b->color),
		forward = min_pos + freq < (int)v.size() && v[min_pos + freq].b != nullptr && v[min_pos + freq].b->color == b->color;

	int num = 0;
	bool dir;

	if (v[min_pos].b->color != b->color && (forward || backward))
	{
		insert_pos_search(min_pos, num, dir);
		if (dir == 1 && forward)
			min_pos += freq;
		if (dir == 0 && backward)
			min_pos -= freq;
		num = -1;
	}
	if (min_val <= b->get_rad() + v[min_pos].b->get_rad())
	{
		b->collision_detection = false;
		if (v[min_pos].b->color == b->color &&
			((min_pos - freq >= 0 && v[min_pos - freq].b != nullptr && v[min_pos - freq].b->color == b->color) ||
			(min_pos + freq < (int)v.size() && v[min_pos + freq].b != nullptr && v[min_pos + freq].b->color == b->color)))
		{
			double k = 0.02;

			b->set_vel(vec::get_rand(-k, k));
			boom_func(min_pos, 0, k, b->color);
			boom_func(min_pos, freq, k, b->color);
			boom_func(min_pos, -freq, k, b->color);
		}
		else
		{
			b->set_vel(vec());
			insert_func(min_pos, b);
		}
	}
}