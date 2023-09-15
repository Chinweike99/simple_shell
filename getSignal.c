#include "main.h"

/**
 * _callp - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void _call(int cals)
{
	(void)cals;
	write(STDOUT_FILENO, "\nSimple_Shell ", 14);
}

