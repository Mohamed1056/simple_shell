#include "shell.h"

/**
 * str_len - function to compute the
 * length of a string
 * @str: the string to calculate its length
 * Retrurn: x on success
*/

int str_len(char *str)
{
	int x = 0;
	/*after decleration of the variabels*/
	if (!str)
		return (0);
	while (str[x] != '\0')
		x++;
	return (x);
}

/**
 * str_cat - function to concatenates two strings
 * @str1: the first string that we want to add
 * the second string to it
 * @str2: the string to be added
 * Return: ptr
*/

char *str_cat(char *str1, char *str2)
{
	char *ptr;
	/*this pointer will point to str1*/
	ptr = str1;
	while (*str1)
		str1++;
	while (*str2)
		*str1++ = *str2++;
	*str1 = *str2;
	return (ptr);
}

/**
 * starts_with - function to check the start of strings
 * @str1: 1st input for the function
 * @str2: 2nd input for the function
 * Return: the new result
*/

char *starts_with(const char *str1, const char *str2)
{
	while (*str2)
		if (*str1++ != *str2++)
			return (NULL);
	return ((char *)str1);
}

/**
 * str_cmp - function to check two strings
 * @str1: first input for the function
 * @str2: second input for the function
*/

int str_cmp(char *str1, char *str2)
{
	while (*str2 && *str1)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
