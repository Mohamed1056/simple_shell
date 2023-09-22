#include "shell.h"

/**
 *my_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * Return: Always 0
 */
int my_env(info_t *info)
{
print_list_str(info->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @myinfo: Structure containing potential arguments. Used to maintain
 * @myname: env var name
 *
 * Return: the value
 */
char *get_env(info_t *myinfo, const char *myname)
{
	list_t *nod = myinfo->env;
	char *pop;
	/*after decleration of variables*/
	while (nod)
	{
		pop = starts_with(nod->str, myname);
		if (pop && *pop)
			return (pop);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * my_unsetenv - Remove an environment variable
 * @myinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_unsetenv(info_t *myinfo)
{
	int m;
	/*after decleration of variable*/
	if (myinfo->argc == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (m = 1; m <= myinfo->argc; m++)
		unset_env(myinfo, myinfo->argv[m]);
	/*the returning value of the code*/
	return (0);
}

/**
 * my_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
