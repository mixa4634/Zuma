#include "ball_creator.h"
#include "road.h"
#include "ball.h"

ball_creator::ball_creator(unsigned int num, double radius, unsigned int r_freq) :
	base_num(num),
	radius(radius),
	r_freq(r_freq)
{
	type = ball_creator_t;
	counter = r_counter = 0;
	curr_num = base_num;
}

ball_creator::~ball_creator()
{
}

void ball_creator::render()
{
	road &ref = road::get_inst();

	if (ref.v[0].b == nullptr)
		if (r_counter >= r_freq - 1)
		{
			if (counter > base_num + curr_num)
			{
				counter = 0;
				curr_num = 2.0 / 3 * base_num + rand() % (int)(2.0 / 3 * base_num) + 1;
			}
			else
			{
				if (counter < curr_num)
				{
					ref.v[0].b = new ball(radius, vec(0, 0, 0), vec(0, 0, 0), ball::get_next_color());
					anim::get_ref() << ref.v[0].b;
				}
				++counter;
			}
			r_counter = 0;
		}
		else
			++r_counter;
}