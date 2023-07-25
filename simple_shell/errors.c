#include "shell.h"

/**
 * _eputs - Prints an input string to stderr.
 * @str: The string to be printed.
 */
void _eputs(char *str)
{
	if (str)
		write(2, str, _strlen(str));
}

/**
 * _eputchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	return write(2, &c, 1);
}

/**
 * _putfd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	return write(fd, &c, 1);
}

/**
 * _putsfd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return 0;

	while (*str)
	{
		i += _putfd(*str++, fd);
	}

	return i;
}

