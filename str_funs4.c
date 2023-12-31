#include "shell.h"

/**
 * str_two - function to split the text
 * @str: takes the string for the function
 * @ptr: the separator for the function
 * Return: txt
*/

char **str_two(char *str, char *ptr)
{
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int num = 0;
	char **txt;
	/*after decleration of all variables*/
	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!ptr)
		ptr = " ";
	while (str[a] != '\0')
	{
		if (!is_it_delim(str[a], ptr) &&
				(is_it_delim(str[a + 1], ptr) || !str[a + 1]))
			num++;
		a++;
	}
	if (num == 0)
		return (NULL);
	txt = malloc(sizeof(char *) * (num + 1));
	if (!txt)
		return (NULL);
	for (a = 0, b = 0; b < num; b++)
	{
		while (is_it_delim(str[a], ptr))
			a++;
		c = 0;
		while (!is_it_delim(str[a + c], ptr) && str[a + c])
			c++;
		txt[b] = malloc(sizeof(char) * (c + 1));
		if (!txt[b])
		{
			for (c = 0; c < b; c++)
				free(txt[c]);
			free(txt);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			txt[b][d] = str[a++];
		txt[b][d] = 0;
	}
	txt[b] = NULL;
	return (txt);
}

/**
 * str_twwo - function to doublacate
 * a string
 * @str: takes the input of the function
 * @z: takes te other input
 * Return: txt
*/
char **str_twwo(char *str, char z)
{
	int a, b, c, d, num = 0;
	char **txt;
	/*after decleration*/
	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != z && str[a + 1] == z) ||
		    (str[a] != z && !str[a + 1]) || str[a + 1] == z)
			num++;
	if (num == 0)
		return (NULL);
	txt = malloc(sizeof(char *) * (num + 1));
	/*checking if the allocation succedd or not*/
	if (!txt)
		return (NULL);
	for (a = 0, b = 0; b < num; b++)
	{
		while (str[a] == z && str[a] != z)
			a++;
		c = 0;
		while (str[a + c] != z && str[a + c] && str[a + c] != z)
			c++;
		txt[b] = malloc(sizeof(char) * (c + 1));
		/*checking the allocation*/
		if (!txt[b])
		{
			for (c = 0; c < b; c++)
				free(txt[c]);
			free(txt);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			txt[b][d] = str[a++];
		txt[b][d] = 0;
	}
	txt[b] = NULL;
	return (txt);
}
