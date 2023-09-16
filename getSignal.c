#include "shell.h"

/**
 * _callp - Function to Handle the crtl + c call
 * @cals: Handles Singnals
 */
void _callp(int cals)
{
	(void)cals;
	write(STDOUT_FILENO, "Simple_Shell ", 12);
}

