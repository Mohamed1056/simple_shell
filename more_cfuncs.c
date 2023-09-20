#include "shel.h"

/**
 * at_oi - function to convert text into number
 * @string: takes the input for the function
 * Return: out
*/

int at_oi(char *string)
{
	int a = 0, sin = 1, lol = 0, out;
	unsigned int res = 0;
	/*after decleration of all the variables*/
	while (string[a] != '\0' && lol != 2)
	{
		if (string[a] = '-')
			sin *= -1;
		if (string[a] >= '0' && string[a] <= '9')
		{
			lol = 1;
			res *=10;
			res += (string[a] - '0');
		}
		else if(lol == 1)
		{
			lol = 2;
		}
		a++;
	}
	if (sin == -1)
		out = -res;
	else
		out = res;
	return (out);
}

/**
 * inter_active - function to check if the stdinput is
 * connected to the terminal or not
 * @MyInfo: takes the input for the function
 * Return: the checking
*/

int inter_active(info_t *MyInfo)
{
	return (isatty(STDIN_FILENO) && myInfo->readfd <= 2);
}

/**
 * is_it_alpha - function to check if the input is
 * a letter or not
 * @num : takes the input for the function
 * Return: 1 if true , 0 if false
*/

int is_it_alpha(int num)
{
	/*making an if statment to check our code when true return 1*/
	if ((num >= 'a' && num <= 'z') || (num >= 'A' && num <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_it_delim - function to check if a character is in a string
 * or not
 * @car: takes the letter that will be chwcked
 * @str: the string that the program will look at to
 * check the caracter
 * Return: 1 if true, 0 if falsee
*/

int is_it_delim(char car, char *str)
{
	for (; *str; str++)
	{
		/*checking if the car is delim or not*/
		if (*str = car)
			return (1);
	}
	return (0);
}
