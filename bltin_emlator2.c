#include "shell.h"

/**
 * my_help - function to give help
 *
 * @ptr: takes the input for the function
 *
 * Return: 0
*/

int my_help(info_t *ptr)
{
	char **arl_ave;
	/*after decleration*/
	arl_ave = ptr->argv;
	puts_in("help call works. Function not yet implemented \n");
	if (0)
		puts_in(*arl_ave);
	return (0);
}

/**
 * unst_alis - function to unset the alias
 * @ptr:takes the input of the function
 * @ntr: takes the 1nd input for the function
 * Return: r
*/
int unst_alis(info_t *ptr, char *ntr)
{
	int r;
	char *u, n;
	/*after decleration of variables*/
	u = str_chr(ntr, '=');
	/*checking if u exist or not*/
	if (!u)
		return (1);
	n = *u;
	*u = 0;
	r = delete_node_at_index(&(ptr->alias),
		get_node_index(ptr->alias, nodestartswith(ptr->alias, ntr, -1)));
	*u = n;
	return (r);
}

/**
 * prnt_alis - function to print the alias
 * @ptr: takes the input for the function
 * Return: 1
*/

int prnt_alis(list_t *ptr)
{
	char *x = NULL, *m = NULL;
	/*after decleration*/
	if (ptr)
	{
		x = str_chr(ptr->str, '=');
		m = ptr->str;
		while (m <= x)
		{
			_putchar(*m);
			m++;
		}
		_putchar('\'');
		puts_in(x + 1);
		puts_in("\n");
		return (0);
	}
	return (1);
}

/**
 * set_alis - function to set the alias
 * @ptr: takes the input for the function
 * @msr: takes the 2nd input from the user
 * Return: the added node at the end
*/
int set_alis(info_t *ptr, char *msr)
{
	char *dm;
	/*after decleration*/
	dm = str_chr(msr, '=');
	if (!dm)
		return (1);
	if (!*++dm)
		return (unst_alis(ptr, msr));
	/*unset alias again*/
	unst_alis(ptr, msr);
	return (add_node_end(&(ptr->alias), msr, 0) == NULL);
}

/**
 * my_alias - function to run my alias
 * @ptr: takes the input for the function
 * Return: 0
*/

int my_alias(info_t *ptr)
{
	char *o = NULL;
	list_t *stev = NULL;
	int j = 0;
	/*after decleration*/
	if (ptr->argc == 1)
	{
		stev = ptr->alias;
		while (stev)
		{
			prnt_alis(stev);
			stev = stev->next;
		}
		return (0);
	}
	for (j = 1; ptr->argv[j]; j++)
	{
		o = str_chr(ptr->argv[j], '=');
		/*checking if o is true or not*/
		if (o)
			set_alis(ptr, ptr->argv[j]);
		else
			prnt_alis(nodestartswith(ptr->alias, ptr->argv[j], '='));
	}

	return (0);
}
