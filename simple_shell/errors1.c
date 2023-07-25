#include "shell.h"

/**
 * _erratoi - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: The converted number if successful, or -1 on error.
 */
int _erratoi(char *s)
{
	int result = 0;

	while (*s)
	{
		if (*s >= '0' && *s <= '9')
		{
			result = result * 10 + (*s - '0');
			if (result > INT_MAX)
				return -1;
		}
		else
			return -1;
		s++;
	}
	return result;
}

/**
 * print_error - Prints an error message.
 * @info: The parameter and return info struct.
 * @estr: String containing the specified error type.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int count = 0;
	unsigned int _abs_, current;

	int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;
	do
	{
		__putchar('0' + current / 10);
		count++;
		current %= 10;
	} while (_abs_ /= 10);

	__putchar('0' + current);
	count++;

	return count;
}

/**
 * convert_number - Converts a number to a string in a specified base.
 * @num: The number to be converted.
 * @base: The base to convert the number into.
 * @flags: Argument flags.
 * Return: The converted string.
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? -num : num;
	static char *array = "0123456789ABCDEF";

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (num < 0 && !(flags & CONVERT_UNSIGNED))
		*--ptr = '-';

	return ptr;
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
