#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shloop(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin = 0;

    while (r != -1 && builtin != -2)
    {
        clearinf(info);
        if (inter_active(info))
            _puts("$ ");
        e_putchar(BUF_FL);
        r = get_input(info);
        if (r != -1)
        {
            _setinf(info, av);
            builtin = findbuiltin(info);
            if (builtin == -1)
                findcmd(info);
        }
        else if (inter_active(info))
            _putchar('\n');
        _freeinf(info, 0);
    }
    writehistory(info);
    _freeinf(info, 1);
    if (!inter_active(info) && info->status)
        exit(info->status);
    if (builtin == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin);
}

/**
 * findbuiltin - finds a builtin
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit
 */
int findbuiltin(info_t *info)
{
    int i, builtin = -1;
    builtintable builtintbl[] = {
        {"exit", my_exit},
        {"env", my_env},
        {"help", my_help},
        {"history", my_history},
        {"setenv", my_setenv},
        {"unsetenv", my_unsetenv},
        {"cd", my_cd},
        {"alias", my_alias},
        {NULL, NULL}};

    for (i = 0; builtintbl[i].type; i++)
        if (str_cmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            builtin = builtintbl[i].func(info);
            break;
        }
    return (builtin);
}

/**
 * findcmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findcmd(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!is_it_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = Path_Find(info, get_env(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    else
    {
        if ((inter_active(info) || get_env(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            fork_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            prnt_err(info, "not found\n");
        }
    }
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {

        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            _freeinf(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
