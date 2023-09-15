#include "shell.h"

/**
 * assignLine - Function that assigns the line variable
 * @ptr: Buffer that store the input str
 * @buff: str that is been called to line
 * @v: The line size
 * @y: The buffer size
 */
void assignLine(char **ptr, size_t *v, char *buff, size_t y)
{

	if (*ptr == NULL)
	{
		if  (y > BUFSIZE)
			*v = y;

		else
			*v = BUFSIZE;
		*ptr = buff;
	}
	else if (*v < y)
	{
		if (y > BUFSIZE)
			*v = y;
		else
			*v = BUFSIZE;
		*ptr = buff;
	}
	else
	{
		_strcpy(*ptr, buff);
		free(buff);
	}
}
/**
 * getLine - Function to Read input from stream
 * @ptr: The buffer that stores input
 * @v: ptr size
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t getLine(char **ptr, size_t *v, FILE *stream)
{
	int x;
	static ssize_t str;
	ssize_t reval;
	char *buff;
	char t = 'z';

	if (str == 0)
		fflush(stream);
	else
		return (-1);
	str = 0;

	buff = malloc(sizeof(char) * BUFSIZE);
	if (buff == 0)
		return (-1);
	while (t != '\n')
	{
		x = read(STDIN_FILENO, &t, 1);
		if (x == -1 || (x == 0 && str == 0))
		{
			free(buff);
			return (-1);
		}
		if (x == 0 && str != 0)
		{
			str++;
			break;
		}
		if (str >= BUFSIZE)
			buff = _realloc(buff, str, str + 1);
		buff[str] = t;
		str++;
	}
            
	buff[str] = '\0';
	assignLine(ptr, v, buff, str);
	reval = str;
	if (x != 0)
		str = 0;
            free(buff)
	return (reval);
}

