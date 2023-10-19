#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t c = 0;
	size_t len_g = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		c = getline(buf, &len_g, stdin);
#else
		c = _getline(info, buf, &len_g);
#endif
		if (c > 0)
		{
			if ((*buf)[c - 1] == '\n')
			{
				(*buf)[c - 1] = '\0';
				c--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = c;
				info->cmd_buf = buf;
			}
		}
	}
	return (c);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t t, v, len;
	ssize_t c = 0;
	char **buf_g = &(info->arg), *g;

	_putchar(BUF_FLUSH);
	c = input_buf(info, &buf, &len);
	if (c == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		v = t; /* init new iterator to current buf position */
		g = buf + t; /* get pointer for return */

		check_chain(info, buf, &v, t, len);
		while (v < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &v))
				break;
			v++;
		}

		t = v + 1; /* increment past nulled ';'' */
		if (t >= len) /* reached end of buffer? */
		{
			t = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_g = g; /* pass back pointer to current command position */
		return (_strlen(g)); /* return length of current command */
	}

	*buf_g = buf; /* else not a chain, pass back buffer from _getline() */
	return (c); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @t: size
 *
 * Return: c
 */
ssize_t read_buf(info_t *info, char *buf, size_t *t)
{
	ssize_t c = 0;

	if (*t)
		return (0);
	c = read(info->readfd, buf, READ_BUF_SIZE);
	if (c >= 0)
		*t = c;
	return (c);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t t, len;
	size_t k;
	ssize_t c = 0, s = 0;
	char *g = NULL, *new_g = NULL, *q;

	g = *ptr;
	if (g && length)
		s = *length;
	if (t == len)
		t = len = 0;

	c = read_buf(info, buf, &len);
	if (c == -1 || (c == 0 && len == 0))
		return (-1);

	q = _strchr(buf + t, '\n');
	k = q ? 1 + (unsigned int)(q - buf) : len;
	new_g = _realloc(g, s, s ? s + k : k + 1);
	if (!new_g) /* MALLOC FAILURE! */
		return (g ? free(g), -1 : -1);

	if (s)
		_strncat(new_g, buf + t, k - t);
	else
		_strncpy(new_g, buf + t, k - t + 1);

	s += k - t;
	t = k;
	g = new_g;

	if (length)
		*length = s;
	*ptr = g;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
