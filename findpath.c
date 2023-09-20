#include "shell.h"

/**
 * Chars_Dup - function to help finding the path
 * @str: takes the hole link of the path
 * @num1: takes the start
 * @num2: takes the end
 * Return: name
*/

char *Chars_Dup(char *str, int num1, int num2)
{
	int a = 0, b = 0;
	static char name[1024];
	/*after declaration of all variables*/
	for (b = 0, a = num1; a < num2; a++)
	{
		if (str[a] != ':')
			name[b++] = str[a];
	}
	/*making the last vale equal to 0*/
	name[b] = 0;
	return (name);
}

/**
 * is_it_cmd - function for helping find the path
 * @str: takes the input for the function
 * @ptr: takes the second input for the function
 * Return: 0
*/

int is_it_cmd(info_t *str, char *ptr)
{
	struct stat ft;
	/*after decleration of the structure*/
	(void)str;
	if (!str || stat(str, &ft))
		return (0);
	if (ft.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * Path_Find - function that find exact path
 * @str: takes the input for the function
 * @ptr1: takes the total path
 * @ptr2: takes the file name
 * Return: path
*/

char *Path_Find(info_t *str, char *ptr1, char *ptr2)
{
	char *path;
	int a, car_pos = 0;
	/*after decleration of the variables*/
	if (!ptr1)
		return (NULL);
	if ((str_len(ptr2) > 2) && starts_with(ptr2, "./"))
	{
		if (is_it_cmd(str, ptr2))
			return (ptr2);
	}
	while (1)
	{
		if (!ptr1[a] || ptr1[a] == ':')
		{
			path = Chars_Dup(ptr1, car_pos, a);
			if (!*path)
				str_cat(path, ptr2);
			else
			{
				str_cat(path, "/");
				str_cat(path, ptr2);
			}
			if (is_it_cmd(str, path))
				return (path);
			if (!ptr1[a])
				break;
			car_pos = a;
		}
		a++;
	}
	return (NULL);
}
