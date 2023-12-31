#ifndef SHELL_H
#define SHELL_H

/*inserting required header files*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FL -1
#define USEGETLINE 0


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USESTRTOK 0

#define HIST_FILE	"shell_history"
#define HIST_MAX	4096

extern char **environ;



/* linked list*/ 
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} list_t;

/*checking function*/
int at_oi(char *);
int is_it_alpha(int);
int is_it_delim(char, char *);


/*functions dealing with memory*/
void *re_allocate(void *, unsigned int, unsigned int);
char *mem_set(char *, char, unsigned int);

/*functions2 dealing with memory*/
void fofree(char **);
int befree(void **);

/*functions to deal with strings*/
int str_len(char *);
char *str_cat(char *, char *);
char *starts_with(const char *, const char *);
int str_cmp(char *, char *);

/*functions2 to deal with strings*/
void puts_in(char *);
char *str_cpy(char *, char *);
int _putchar(char);
char *str_dup(const char *);

/*functions3 to deal with strings*/
char *strn_copy(char *, char *, int);
char *str_chr(char *, char);
char *strn_cat(char *, char *, int);

/*functions4 to deal with strings*/
char **str_two(char *, char *);
char **str_twwo(char *, char);
void _puts(char *);

int put_fd(char c, int fd);
void e_puts(char *);
int puts_fd(char *str, int fd);
int e_putchar(char);


typedef struct passinformation
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;
int shloop(info_t *, char **);
/*checking functions2*/
int prnt_d(int, int);
int err_atoi(char *);
char *Convert_Number(long int, int, int);
void prnt_err(info_t *, char *);
void Remove_Comments(char *);
int inter_active(info_t *);
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
} builtin_table;

/*functios to find the path*/
char *Chars_Dup(char *, int, int);
int is_it_cmd(info_t *, char *);
char *Path_Find(info_t *, char *, char *);

/*the built in emuliators*/
int my_cd(info_t *);
int my_exit(info_t *);
int my_history(info_t *);

/*the built in emuilators2*/
int my_help(info_t *);
int my_alias(info_t *);


int BuildHlist(info_t *information, char *buff, int linec);
/* getline */
ssize_t get_input(info_t *);
int get_l(info_t *, char **, size_t *);
void sigintHandler(int);
/* chains.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replacealias(info_t *);
int replacevar(info_t *);
int replacestring(char **, char *);
/*list*/

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *nodestartswith(list_t *, char *, char);
int readhistory(info_t *info);
char *gethistoryfile(info_t *info);
int writehistory(info_t *info);
int renumberhistory(info_t *info);
/*loop*/
int findbuiltin(info_t *);
void findcmd(info_t *);
void fork_cmd(info_t *);
/*env*/
int my_env(info_t *);
char *get_env(info_t *, const char *);
int my_unsetenv(info_t *);
int populate_env_list(info_t *);
int my_setenv(info_t *);
char **get_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/*information*/
void clearinf(info_t *);
void _freeinf(info_t *, int);
void _setinf(info_t *, char **);
#endif
