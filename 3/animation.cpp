#include "animation.h"
#include "game_logic.h"

using namespace std;

anim anim::instance;

anim::anim(void) :
	pos(0, 0, 1),
	dir(0, 0, 0),
	up(0, 1, 0)
{
	FreeConsole();

	instance.height = glutGet(GLUT_SCREEN_HEIGHT);
	instance.width = glutGet(GLUT_SCREEN_WIDTH);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	win_id = glutCreateWindow("OpenGL"); 

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(instance.display); 
	glutReshapeFunc(instance.reshape);
	glutKeyboardFunc(instance.keyboard);
	glutMouseFunc(instance.mouse_button);
	glutMotionFunc(instance.mouse_move);
	glutIdleFunc(instance.idle);
	glutFullScreen(); 

	QueryPerformanceFrequency(&frequency); 
	QueryPerformanceCounter(&start_time);

	time = 0;
	scene = menu_creating;
	total_vel = 1;
}

void anim::display(void) 
{
	game_logic::game_logic_1(instance);
	instance.clear_stack();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	instance.set_camera(instance.pos, instance.dir, instance.up);
	glColor3d(1, 1, 1);
	for (unsigned int i = 0; i < instance.stack.size(); ++i)
		instance.stack[i]->render();
	for (unsigned int i = 0; i < instance.stack.size(); ++i) 
		instance.stack[i]->draw();
	glPopMatrix();
	glFinish();
	glutSwapBuffers();
}

void anim::set_camera(vec &pos, vec &dir, vec &up) 
{
	glLoadIdentity();
	gluLookAt(pos.x, pos.y, pos.z,
		dir.x, dir.y, dir.z,
		up.x, up.y, up.z);
}

void anim::clear_stack()
{
	double 
		x_max_pos = pos.z * 2, 
		y_max_pos = x_max_pos * width / height;

	for (int i = 0; i < (signed int)stack.size(); ++i)
		if (abs(stack[i]->pos.x) > x_max_pos || abs(stack[i]->pos.y) > y_max_pos)
		{
			delete stack[i];
			stack.erase(stack.begin() + i--);
		}
}

void anim::reshape(int width, int height) 
{
	double size = 40;

	glutPositionWindow(0, 0);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (double) width / height, 0.001, size);
	glMatrixMode(GL_MODELVIEW);
}

void anim::keyboard(unsigned char key, int x, int y) 
{
	if (key == 27) 
	{
		exit(0);
	}
	for (unsigned int i = 0; i < instance.stack.size(); i++) 
		instance.stack[i]->keyboard(key, x, y);
}

void anim::mouse_button(int button, int state, int mouse_x, int mouse_y)
{
	for (unsigned int i = 0; i < instance.stack.size(); i++)
		instance.stack[i]->mouse_button(button, state, mouse_x, mouse_y);
}

void anim::mouse_move(int mouse_x, int mouse_y)
{
	for (unsigned int i = 0; i < instance.stack.size(); i++)
		instance.stack[i]->mouse_move(mouse_x, mouse_y);
}

void anim::idle(void) 
{
	LARGE_INTEGER tmp_time;

	QueryPerformanceCounter(&tmp_time);
	instance.time = (tmp_time.QuadPart - instance.start_time.QuadPart) * 1.0 / instance.frequency.QuadPart;
	glutPostRedisplay();
}

void anim::clear_scene(void)
{
	for (unsigned int i = 0; i < instance.stack.size(); i++)
		delete instance.stack[i];
	instance.stack.clear();
}

double anim::get_time(void)
{
	return instance.time;
}

anim::~anim()
{
	for (unsigned int i = 0; i < instance.stack.size(); i++)
		delete instance.stack[i];
}