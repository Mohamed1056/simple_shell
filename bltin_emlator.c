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
	if (!str)
		puts_in("TODO: >>getcwd failure emsg here<<\n");
	if (!stu->argv[1])
	{
		ptr = get_env(stu, "HOME=");
		if (!ptr)
			ch = chdir((ptr = get_env(stu, "PWD=")) ? ptr : "/");
		else
			ch = chdir(ptr);
	}
	else if (str_cmp(stu->argv[1], "-") == 0)
	{
		if (!get_env(stu, "OLDPWD="))
		{
			puts_in(str);
			_putchar('\n');
			return (1);
		}
		puts_in(get_env(stu, "OLDPWD=")), _putchar('\n');
		ch = chdir((ptr = get_env(stu, "OLDPWD=")) ? ptr : "/");
	}
	else
		ch = chdir(stu->argv[1]);
	if (ch == -1)
	{
		prnt_err(stu, "can't cd to ");
		e_puts(stu->argv[1]), e_putchar('\n');
	}
	else
	{
		set_env(stu, "OLDPWD", get_env(stu, "PWD="));
		set_env(stu, "PWD", getcwd(example, 1024));
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
			e_puts(ptr->argv[1]);
			e_putchar('\n');
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
