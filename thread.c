#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @c: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *c)
{
	int j = 0;

	if (!c)
		return (0);

	while (*c++)
		j++;
	return (j);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @c1: the first strang
 * @c2: the second strang
 *
 * Return: negative if c1 < c2, positive if c1 > c2, zero if c1 == c2
 */
int _strcmp(char *c1, char *c2)
{
	while (*c1 && *c2)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	if (*c1 == *c2)
		return (0);
	else
		return (*c1 < *c2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *rick, const char *needle)
{
	while (*needle)
		if (*needle++ != *rick++)
			return (NULL);
	return ((char *)rick);
}

/**
 * _strcat - concatenates two strings
 * @final: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *final, char *src)
{
	char *ret = final;

	while (*final)
		final++;
	while (*src)
		*final++ = *src++;
	*final = *src;
	return (ret);
}
