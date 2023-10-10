#include "shell.h"

/**
 * good - good a pointer and NULLs the address
 * @stry: address of the pointer to good
 *
 * Return: 1 if good, otherwise 0.
 */
int good(void **stry)
{
	if (stry && *stry)
	{
		good(*stry);
		*stry = NULL;
		return (1);
	}
	return (0);
}
