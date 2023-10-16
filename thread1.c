#include "shell.h"

/**
 * _strcpy - copies a string
 * @final: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *final, char *src)
{
	int j = 0;

	if (final == src || src == 0)
		return (final);
	while (src[j])
	{
		final[j] = src[j];
		j++;
	}
	final[j] = 0;
	return (final);
}

/**
 * _strdup - duplicates a string
 * @thr: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *thr)
{
	int length = 0;
	char *ret;

	if (thr == NULL)
		return (NULL);
	while (*thr++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--thr;
	return (ret);
}

/**
 *_puts - prints an input string
 *@thr: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *thr)
{
	int j = 0;

	if (!thr)
		return;
	while (thr[j] != '\0')
	{
		_putchar(thr[j]);
		j++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char g)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (g == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (g != BUF_FLUSH)
		buf[j++] = g;
	return (1);
}
