#include "shell.h"
/**
 * main - entry point for the program
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success,1 if an error happened
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				e_puts(av[0]);
				e_puts(": 0: Can't open ");
				e_puts(av[1]);
				e_putchar('\n');
				e_putchar(BUF_FL);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	readhistory(info);
	shloop(info, av);
	return (EXIT_SUCCESS);
}
