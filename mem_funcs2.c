#include "shell.h"

/**
 * fofree - function to free the memory
 * @str: takes the input for the function
 * Retuurn: void
*/

void fofree(char **str)
{
	char **ptr = str;
	/*checking the existance of str*/
	if (!str)
		return;
	if (str == NULL)
	{
		free(str);
		return;
	}
	do {
		free(*str);
	} while (*++str);
	free(ptr);
}

/**
 * befree - function to free the memory
 * @str: takes the input of the function
 * Return: 0
*/

int befree(void **str)
{
	/*checking the existance of str and its pointer*/
	if (str && *str)
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	return (0);
}
