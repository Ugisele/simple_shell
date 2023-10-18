#include "shell.h"

/**
 * list_len - determines length of linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_typ*p)
{
	size_t k = 0;

	while (p)
	{
		p = p->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_typ*head)
{
	list_typ*node = head;
	size_t k = list_len(head), r;
	char **strs;
	char *str;

	if (!head || !k)
		return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (r = 0; r < k; r++)
				free(strs[r]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[k] = str;
	}
	strs[k] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_typlinked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_typ*p)
{
	size_t k = 0;

	while (p)
	{
		_puts(convert_number(p->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		k++;
	}
	return (k);
}

/**
 * node_starts_with - returns node whose string starts with adjunct
 * @node: pointer to list head
 * @H: string to match
 * @c: the next character after adjunct to match
 *
 * Return: match node or null
 */
list_typ*node_starts_with(list_typ*node, char *adjunct, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, adjunct);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_typ*head, list_typ*node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}
