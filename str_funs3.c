#include "shell.h"

/**
 * strn_copy - function to copy the string in
 * another variable using limited number of byts
 * @str1: the copy will be saved in this variable
 * @str2: takes the input for the function
 * @a: make the copy for a limited number of letters
 * Return: ptr
*/

char *strn_copy(char *str1, char *str2, int a)
{
	int b = 0, c;
	char *ptr = str1;
	/*after decleration*/
	while (str2 != NULL && b < a - 1)
	{
		str1[b] = str2[b];
		b++;
	}
	if (b < a)
	{
		c = b;
		while (c < a)
		{
			str1[c] = '\0';
			c++;
		}
	}
	return (ptr);
}

/**
 * str_chr - function to find the wanted letter
 * in a string or text
 * @text: takes the word that we want to search
 * inside it
 * @letter: the letter we want to find
 * Return: the letter if true and NULL if false
*/

char *str_chr(char *text, char letter)
{
	while (*text != '\0')
	{
		if (*text == letter)
			return (text);
	text++;
	}
	return (NULL);
}

/***/

char *strn_cat(char *str, char *ptr, int num)
{
	int p = 0;
	char *txt = str;
	/*after decleration of the variables*/
	while (*str != '\0')
		str++;
	/*this loop is for adding letters from ptr to str*/
	while (*ptr != '\0' && p < num)
	{
		*str = *ptr;
		str++;
		ptr++;
		p++;
	}
	if (p < num)
		str[p] = '\0';
	return (txt);
}
