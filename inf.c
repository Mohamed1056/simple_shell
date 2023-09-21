#include "shell.h"

/**
 * clearinf - initializes info_t struct
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
 * _setinf - initializes info_t struct
 * @myinfo: struct address
 * @auv: argument vector
 */
void _setinf(info_t *myinfo, char **auv)
{
	int i = 0;
	/*after decleration of xyz*/
	myinfo->fname = auv[0];
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
		for (i = 0; myinfo->argv && myinfo->argv[i]; i++)
			;
		myinfo->argc = i;

		replacealias(myinfo);
		replacevar(myinfo);
	}
}

/**
 * _freeinf - frees info_t struct fields
 * @myinfo: struct address
 * @lol: true if freeing all fields
 */
void _freeinf(info_t *myinfo, int lol)
{
	fofree(myinfo->argv);
	myinfo->argv = NULL;
	myinfo->path = NULL;
	if (lol)
	{
		if (!myinfo->cmd_buf)
			free(myinfo->arg);
		if (myinfo->env)
			free_list(&(myinfo->env));
		if (myinfo->history)
			free_list(&(myinfo->history));
		if (myinfo->alias)
			free_list(&(myinfo->alias));
		fofree(myinfo->environ);
		myinfo->environ = NULL;
		befree((void **)myinfo->cmd_buf);
		if (myinfo->readfd > 2)
		close(myinfo->readfd);
		_putchar(BUF_FL);
	}
}
