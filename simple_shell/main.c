#include "shell.h"

/**
 * _eputchar - writes a character to the standard error stream
 * @c: the character to be written
 *
 * Return: On success, the character written is returned.
 * On error, EOF is returned, and errno is set appropriately.
 */
int _eputchar(int c)
{
	return write(STDERR_FILENO, &c, 1);
}

/**
 * _eputs - writes a string to the standard error stream
 * @str: the string to be written
 *
 * Return: On success, the number of characters written is returned.
 * On error, EOF is returned, and errno is set appropriately.
 */
int _eputs(const char *str)
{
	int len = 0;

	while (str[len])
	{
		if (_eputchar(str[len]) == EOF)
			return EOF;
		len++;
	}

	return len;
}

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info = INFO_INIT;

	if (ac == 2)
	{
		int fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eprintf("%s: 0: Can't open %s\n", av[0], av[1]);
				exit(127);
			}
			return EXIT_FAILURE;
		}
		info.readfd = fd;
	}

	populate_env_list(&info);
	read_history(&info);
	hsh(&info, av);

	return EXIT_SUCCESS;
}
