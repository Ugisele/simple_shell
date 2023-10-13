#include "shell.h"

/**
 **_memoryset - fills memory with a constant byte
 *@m: the pointer to the memory area
 *@p: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (m) a pointer to the memory area m
 */
char *_memoryset(char *m, char p, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		m[i] = p;
	return (m);
}

/**
 * _ffree - frees a string of strings
 * @hh: string of strings
 */
void _ffree(char **hh)
{
	char **a = hh;

	if (!hh)
		return;
	while (*hh)
		free(*hh++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the old block name.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *d;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	d = malloc(new_size);
	if (!d)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		d[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (d);
}
