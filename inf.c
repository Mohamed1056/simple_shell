#include "shell.h"

/**
 * clear_nfo - initializes info_t struct
 * @myinfo: struct address
 */
void clearinf(info_t *myinfo)
{
	/*no variables to declare here*/
	myinfo->arg = NULL;
	myinfo->argv = NULL;
	myinfo->path = NULL;
	myinfo->argc = 0;
}

/**
 * _setinfo - initializes info_t struct
 * @myinfo: struct address
 * @auv: argument vector
 */
void _setinf(info_t *myinfo, char **auv)
{
	int i = 0;
	/*after decleration of xyz*/
	myinfo->fname = av[0];
	/*checking the code*/
	if (myinfo->arg)
	{
		myinfo->argv = str_two(myinfo->arg, " \t");
		if (!myinfo->argv)
		{
			myinfo->argv = malloc(sizeof(char *) * 2);
			if (myinfo->argv)
			{
				myinfo->argv[0] = str_dup(myinfo->arg);
				myinfo->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		myinfo->argc = i;

		replacealias(myinfo);
		replacevar(myinfo);
    }
}

/**
 * _freeinf
 * - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void _freeinf(info_t *info, int all)
{
    fofree(info->argv);
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
        fofree(info->environ);
        info->environ = NULL;
        befree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FL);
    }
}
