#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t x = 0;
	char *pt;

	if (!node || !var)
		return (0);

	while (node)
	{
		pt = starts_with(node->str, var);
		if (pt && *pt == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), x);
			x = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (info->env_changed);
}

/**
 *_set_env - Initialize a new environment variable,
 * @info: Structure containing potential arguments. Used to maintain
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *pt;

	if (!var || !value)
		return (0);

	buff = malloc(str_len(var) + str_len(value) + 2);
	if (!buff)
		return (1);
	str_cpy(buff, var);
	str_cat(buff, "=");
	str_cat(buff, value);
	node = info->env;
	while (node)
	{
		pt = starts_with(node->str, var);
		if (pt && *pt == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
