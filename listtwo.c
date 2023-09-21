#include "shell.h"

/**
 * list_len length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t b = 0;

	while (h)
	{
		h = h->next;
		b++;
	}
	return (b);
}

/**
 * list_to_strings - returns an array of strings of the list
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strx;
	char *str;

	if (!head || !i)
		return (NULL);
	strx = malloc(sizeof(char *) * (i + 1));
	if (!strx)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strx[j]);
			free(strx);
			return (NULL);
		}
		str = str_cpy(str, node->str);
		strx[i] = str;
	}
	strx[i] = NULL;
	return (strx);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		puts_in(Convert_Number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		puts_in(h->str ? h->str : "(nil)");
		puts_in("\n");
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodestartswith(list_t *node, char *prefix, char c)
{
	char *p = NULL;
	/*after declearion*/
	while (node)
	{
		p = starts_with(node->str, prefix);
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
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}
