#include "shell.h"

/**	
 * findbuiltin - function to build in
 *
 * @ptr: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit
 */
int findbuiltin(info_t *ptr)
{
	int num, liv2 = -1;
	builtin_table liv[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}};
	/*after decleration of all variales*/
	for (num = 0; liv[num].type; num++)
		if (str_cmp(ptr->argv[0], liv[num].type) == 0)
		{
			ptr->line_count++;
			liv2 = liv[num].func(ptr);
			break;
		}
		return (liv2);
}

/**
 * findcmd - finds a command in PATH
 * @myinfo: the parameter & return info struct
 *
 * Return: void
 */
void findcmd(info_t *myinfo)
{
	int a, b;
	char *path_now = NULL;

	myinfo->path_now = myinfo->argv[0];
	if (myinfo->linecount_flag == 1)
	{
		myinfo->line_count++;
		myinfo->linecount_flag = 0;
	}
	for (a = 0, b = 0; myinfo->arg[a]; a++)
		if (!is_it_delim(myinfo->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path_now = Path_Find(myinfo, get_env(myinfo, "PATH="), myinfo->argv[0]);
	if (path_now)
	{
		myinfo->path_now = path_now;
		fork_cmd(myinfo);
	}
	else
	{
		if ((inter_active(myinfo) || get_env(myinfo, "PATH=") || myinfo->argv[0][0] == '/') && is_it_cmd(myinfo, myinfo->argv[0]))
			fork_cmd(myinfo);
		else if (*(myinfo->arg) != '\n')
		{
			myinfo->status = 127;
			prnt_err(info, "not found\n");
		}
	}
}
/**
 * shloop - function to make loop
 * @myinfo: takes the input for the function
 * @auv: takes the other input for the function
 * Return: builtinhere
*/

int shloop(info_t *myinfo, char **auv)
{
        int builtinhere = 0;
	ssize_t res = 0;
	/*after decleration*/
        while (res != -1 && builtinhere != -2)
        {
                clearinf(myinfo);
                if (inter_active(myinfo))
                        puts_in("$ ");
                e_putchar(BUF_FL);
                res = get_input(myinfo);
                if (res != -1)
                {
                        _setinf(myinfo, auv);
                        builtinhere = findbuiltin(info);
                        if (builtinhere == -1)
                                findcmd(myinfo);
                }
                else if (inter_active(myinfo))
                        _putchar('\n');
                _freeinf(myinfo, 0);
        }
        writehistory(myinfo);
        _freeinf(myinfo, 1);
        if (!inter_active(myinfo) && myinfo->status)
                exit(myinfo->status);
        if (builtinhere == -2)
        {
                if (myinfo->err_num == -1)
                        exit(myinfo->status);
                exit(myinfo->err_num);
        }
        return (builtinhere);
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @ptr: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *ptr)
{
	pid_t chld_pid;
	/*after decleration*/
	chld_pid = fork();
	if (chld_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (chld_pid == 0)
	{
		if (execve(ptr->path, ptr->argv, get_environ(ptr)) == -1)
		{
			_freeinf(ptr, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(ptr->status));
		if (WIFEXITED(ptr->status))
		{
			ptr->status = WEXITSTATUS(ptr->status);
			if (ptr->status == 126)
				prnt_err(ptr, "Permission denied\n");
		}
	}
}
