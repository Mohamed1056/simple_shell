#include "shell.h"

/**
 * prnt_d - function to check the fd
 * @n: is the input for the function
 * @fd: is the file discretor
 * Return: cont
*/

int prnt_d(int n, int fd)
{
	int (*__putchar)(char) = _putchar;
	int b, cont = 0;
	unsigned int abs_val, crnt;
	/*after decleration of the variables*/
	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	/*checking the code now*/
	if (n < 0)
	{
		abs_val = -n;
		__putchar('-');
		cont++;
	}
	else
		abs_val = n;
	crnt = abs_val;
	/*making another loop to run the code properly*/
	for (b = 1000000000; b > 1; b /= 10)
	{
		if (abs_val / b)
		{
			__putchar('0' + crnt / b);
			cont++;
		}
		crnt %= b;
	}
	__putchar('0' + crnt);
	cont++;

	return (cont);
}

/**
 * err_atoi - function to convert text into numbers and
 * taking into account the errors
 * @str: takes the inpt for the function
 * Return: res
*/

int err_atoi(char *str)
{
	int x = 0;
	unsigned long int res = 0;
	/*after decleration of the variables*/
	if (*str == '+')
		str++;
	/*doing while loop*/
	while (str[x] != '\0')
	{
		if (str[x] >= '0' && str[x] <= '9')
		{
			res *= 10;
			res += (str[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		x++;
	}
	return (res);
}

/**
 * Convert_Number - function to convert numbers to another bases
 * @num: takes the number to be converted
 * @a: the base that the number will be converted to
 * @b: the flags
 * Return: pttr
*/

char *Convert_Number(long int num, int a, int b)
{
	static char var[100];
	static char *str;
	char *pttr;
	char sin = 0;
	unsigned long int x = num;
	/*after decleration of variables*/
	if (!(b & CONVERT_UNSIGNED) && num < 0)
	{
		x = -num;
		sin = '-';
	}
	str = = b & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pttr = &varr[99];
	*pttr = '\0';
	/*while loop*/
	while (x != 0)
	{
		*--pttr = str[x % a];
		x /= a;
	}
	if (sin)
		*--pttr = sin;
	return (pttr);
}

/**
 * prnt_err - function to print errors
 * @MyInfo: takes the input for the function
 * @mastr: takes the 2nd input for the function
 * Return: void
*/

void prnt_err(info_t *MyInfo, char *mastr)
{
	_eputs(MyInfo->fname);
	_eputs(": ");
	/*printing the code*/
	print_d(MyInfo->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(MyInfo->argv[0]);
	_eputs(": ");
	_eputs(mastr);
}

/**
 * Remove_Comments - function to remove comments
 * @str: takes the input of the function
 * Return: nothing
*/

void Remove_Comments(char *str)
{
	int m;
	/*after decleration*/
	for (m = 0; str[m] != '\0'; m++)
	{
		/*cheking using if statment*/
		if (str[m] == '#' && (!m || str[m - 1] == ' '))
		{
			str[m] = '\0';
			break;
		}
	}
}
