#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int g, c;
	char *s = dest;

	g = 0;
	while (src[g] != '\0' && g < n - 1)
	{
		dest[g] = src[g];
		g++;
	}
	if (g < n)
	{
		c = g;
		while (c < n)
		{
			dest[c] = '\0';
			c++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int g, c;
	char *s = dest;

	g = 0;
	c = 0;
	while (dest[g] != '\0')
		g++;
	while (src[c] != '\0' && c < n)
	{
		dest[g] = src[c];
		g++;
		c++;
	}
	if (c < n)
		dest[g] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
