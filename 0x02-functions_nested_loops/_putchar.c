#include "main.h"
#include <unistd.h>
/**
 * _putchar - writes the character to c stdout
 * @c: the character to print
 *
 * return: 1 on sucess
 * on error -1
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
