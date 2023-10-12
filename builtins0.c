#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  return: Always 0
 */
int _myhistory(info_typ *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * return: Always 0 on success, 1 on error
 */
int unset_alias(info_typ *info, char *str)
{
	char *h, c;
	int retrn;

	h = _strchr(str, '=');
	if (!h)
		return (1);
	c = *h;
	*h = 0;
	retrn = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*h = c;
	return (retrn);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * return: Always 0 on success, 1 on error
 */
int set_alias(info_typ *info, char *str)
{
	char *h;

	h = _strchr(str, '=');
	if (!h)
		return (1);
	if (!*++h)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * return: Always 0 on success, 1 on error
 */
int print_alias(list_typ *node)
{
	char *h = NULL, *a = NULL;

	if (node)
	{
		h = _strchr(node->str, '=');
		for (a = node->str; a <= h; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(h + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  return: Always 0
 */
int _myalias(info_typ *info)
{
	int i = 0;
	char *h = NULL;
	list_typ *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		h = _strchr(info->argv[i], '=');
		if (h)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
