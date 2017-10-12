#include <cmath>
#include "game_logic.h"
#include "ball.h"
#include "pad.h"
#include "background.h"
#include "road.h"
#include "ball_creator.h"
#include "score.h"
#include "waiter.h"
#include "menu.h"

void game_logic::game_logic_1(anim & obj)
{
	unsigned int r_freq = 75;
	double val, height = 0.01;
	vec 
		background_color = vec(167.0 / 255, 164.0 / 255, 218.0 / 255),
		road_color = vec(55.0 / 255, 107.0 / 255, 126.0 / 255),
		pad_color = vec(55.0 / 255, 107.0 / 255, 126.0 / 255),
		text_first_color = vec(0, 0, 0),
		text_second_color = vec(0, 0, 1);

	switch (obj.scene)
	{
	case menu_creating:
		anim::get_ref().clear_scene();
		obj << new background(0, background_color);
		obj << new menu(0.1, text_first_color, text_second_color, vec(-1, 0.5, height));
		obj.scene = waiting;
		break;
	case game_proc:
		break;
	case game_start:
		anim::get_ref().clear_scene();
		obj << new background(0, background_color);
		obj << new pad(0.05, vec(0, -0.8, 0), pad_color, 10);
		obj << new road(0.4, height, road_color, [](double x) { return -x * x + sin(x * 5); }, 700, vec(-1.5, 1.3, 0), vec(1.5, -0.7, 0), r_freq, 0.5); //r_freq % ceil(1 / speed) == 0
		obj << new ball_creator(5, 0.05, r_freq);
		obj << new score(vec(1.2, 0, height), text_first_color);
		obj.scene = game_proc;
		break;
	case game_end:
		Sleep(1000);
		val = score::get_inst().get_val();
		anim::get_ref().clear_scene();
		obj << new score(vec(-0.1, 0, height), text_first_color);
		score::get_inst().set_val(val);
		obj << new background(0, background_color);
		obj << new waiter(menu_creating, "Press any key to continue", vec(-0.24, -0.1, height), text_first_color);
		obj.scene = waiting;
		break;
	case waiting:
		break;
	case quit:	
		exit(0);
	default:
		obj.scene = menu_creating;
	}
}