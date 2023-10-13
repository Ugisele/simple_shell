#include "shell.h"

/**
 * clear_info - initializes info_typ struct
 * @info: struct address
 */
void clear_info(info_typ *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_typ struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_typ *info, char **av)
{
	int g = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (g = 0; info->argv && info->argv[g]; g++)
			;
		info->argc = g;

		alias_replace(info);
		vars_replace(info);
	}
}

/**
 * free_info - frees info_typ struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_typ *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}