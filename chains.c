#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @pos: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 if not
 */
int is_chain(info_t *info, char *buff, size_t *pos)
{
	size_t x = *pos;

	if (buff[x] == '|' && buff[x + 1] == '|')
	{
		buff[x] = 0;
		x++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[x] == '&' && buff[x + 1] == '&')
	{
		buff[x] = 0;
		x++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[x] == ';')
	{
		buff[x] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = x;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @pos: address of current position in buf
 * @v: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buff, size_t *pos, size_t v, size_t len)
{
	size_t x = *pos;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[v] = 0;
			x = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[v] = 0;
			x = len;
		}
	}

	*pos = v;
}

/**
 * replacealias - replaces an alias
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 if failed to replace
 */
int replacealias(info_t *info)
{
	int i;
	list_t *node;
	char *m;

	for (i = 0; i < 10; i++)
	{
		node = nodestartswith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		m = str_chr(node->str, '=');
		if (!m)
			return (0);
		m = str_dup(m + 1);
		if (!m)
			return (0);
		info->argv[0] = m;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 in failure
 */
int replacevar(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_cmp(info->argv[i], "$?"))
		{
			replacestring(&(info->argv[i]),
			str_dup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->argv[i], "$$"))
		{
			replacestring(&(info->argv[i]),
			str_dup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = nodestartswith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replacestring(&(info->argv[i]),
			str_dup(str_chr(node->str, '=') + 1));
			continue;
		}
		replacestring(&info->argv[i], str_dup(""));
	}
	return (0);
}

/**
 * replacestring - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 on failure */
int replacestring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
