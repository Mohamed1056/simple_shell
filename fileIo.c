#include "shell.h"

/**
 * gethistoryfile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *gethistoryfile(info_t *info)
{
	char *buff, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	str_cpy(buff, dir);
	str_cat(buff, "/");
	str_cat(buff, HIST_FILE);
	return (buff);
}

/**
 * writehistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writehistory(info_t *info)
{
	ssize_t fd;
	char *fname = gethistoryfile(info);
	list_t *node = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FL, fd);
	close(fd);
	return (1);
}
/**
 * BuildHlist - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int  BuildHlist(info_t *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * readhistory - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readhistory(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, readlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *fname = gethistoryfile(info);

	if (!fname)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	readlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (readlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			 BuildHlist(info, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		BuildHlist(info, buff + last, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumberhistory(info);
	return (info->histcount);
}


/**
 * renumberhistory - renumbers the history linked list
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberhistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
