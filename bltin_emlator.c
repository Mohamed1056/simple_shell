#include "shell.h"

/**
 * my_cd - function to do the cd
 * @stu: takes the input of the function
 * Return: 0
*/

int my_cd(info_t *stu)
{
	int ch;
	char *str, *ptr, example[1024];
	/*after decleration of all variables*/
	str = getcwd(example, 1024);
	/*checking the variable*/
	if (!str)
		puts_in("TODO: >>getcwd failure emsg here<<\n");
	if (!stu->argv[1])
	{
		ptr = _getenv(stu, "HOME=");
		if (!ptr)
			ch = 
				chdir((ptr = _getenv(stu, "PWD=")) ? ptr : "/");
		else
			ch = chdir(ptr);
	}
	else if (str_cmp(stu->argv[1], "-") == 0)
	{
		if (!_getenv(stu, "OLDPWD="))
		{
			puts_in(str);
			_putchar('\n');
			return (1);
		}
		puts_in(_getenv(stu, "OLDPWD=")), _putchar('\n');
		ch = /*This is the second comment here*/
			chdir((ptr = _getenv(stu, "OLDPWD=")) ? ptr : "/");
	}
	else
		ch = chdir(stu->argv[1]);
	if (ch == -1)
	{
		prnt_err(stu, "can't cd to ");
		_eputs(stu->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(stu, "OLDPWD", _getenv(stu, "PWD="));
		_setenv(stu, "PWD", getcwd(example, 1024));
	}
	return (0);
}

/**
 * my_exit - function to exit the program
 * @ptr: takes the input for the function
 * Return: -2
*/

int my_exit(info_t *ptr)
{
	int exhere;
	/*after decleration*/
	if (ptr->argv[1])
	{
		exhere = err_atoi(ptr->argv[1]);
		if (exhere == -1)
		{
			ptr->status = 2;
			prnt_err(ptr, "Illegal number: ");
			_eputs(ptr->argv[1]);
			_eputchar('\n');
			return (1);
		}
		/*after checking exhere variable*/
		ptr->err_num = err_atoi(ptr->argv[1]);
		return (-2);
	}
	/*after ending the condition*/
	ptr->err_num = -1;
	return (-2);
}

/**
 * my_history - function to return history
 * @ptr: takes the input for the function
 * Return: 0
*/

int my_history(info_t *ptr)
{
	/*writing the code after here*/
	print_list(ptr->history);
	return (0);
}
