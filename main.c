#include "shell.h"

/**
 * main - entry point
 * @c: arg count
 * @v: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int c, char **v)
{
	info_typ info[] = { INFO_INIT };
	int cg = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (cg)
		: "r" (cg));

	if (c == 2)
	{
		cg = open(v[1], O_RDONLY);
		if (cg == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(v[0]);
				_eputs(": 0: Can't open ");
				_eputs(v[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readcg = cg;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, v);
	return (EXIT_SUCCESS);
}
