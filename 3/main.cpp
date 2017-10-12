#include <crtdbg.h>
#include "animation.h"

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	anim &instance = anim::get_ref();

	instance.run();

	return 0;
}