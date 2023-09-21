#include "shell.h"

/**
 * puts_in - function to print string
 * @ptr: takes the input for the function
 * Return: void
*/

void puts_in(char *ptr)
{
	int m = 0;
	/*after decleration of variables*/
	if (!ptr)
		return;
	while (ptr[m] != NULL)
	{
		_putchar(ptr[m]);
		m++;
	}
}

/**
 * str_cpy - fuunction to copy the text from
 * the str2 to str1
 * @str1: the string will be copied in it
 * @str2: takes the input for the function
 * Return: srt1
*/

char *str_cpy(char *str1, char *str2)
{
	int x;
	/*after decleration of this variable*/
	if (str1 == str2 || str2 == 0)
		return (str1);
	for (x = 0; str2[x]; x++)
		str1[x] = str2[x];
	str1[x] = '\0';
	return (str1);
}

/**
 * _putchar - function to print character
 * @x: takes the input for the function
 * Return: 1
*/

int _putchar(char x)
{
	static char buuf[WRITE_BUF_SIZE];
	static int n;
	/*using static to make the the variables retain their values*/
	if (x == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buuf, n);
		n = 0;
	}
	if (x != BUF_FLUSH)
		buuf(n++) = x;
	return (1);
}

/**
 * str_dup - function to duplicate the string
 * @text: takes the input for the function
 * Return: ptr
*/

char *str_dup(const char *text)
{
	int height, m;
	char *ptr;
	/*after decleration of the two variables*/
	if (!text)
		return (NULL);
	for (; text[height] != '\0'; height++)
		;
	ptr = malloc(sizeof(char) * (height + 1));
	/*checking if the memory is alocated or not*/
	if (!ptr)
		return (NULL);
	for (m = 0; m < height; m++)
		ptr[m] = text[m];
	return (ptr);
}
