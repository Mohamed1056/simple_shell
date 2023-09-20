#ifndef SHELL_H
#define SHELL_H

/*inserting required header files*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FL -1
#define USEGETLINE 0


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USESTRTOK 0

#define HIST_FILE	"shell_history"
#define HIST_MAX	4096

extern char **environ;


/*checking function*/
int at_oi(char *);
int inter_active(info_t);
int is_it_alpha(int);
int is_it_delim(char, char *);

/*checking functions2*/
int prnt_d(int, int);
int err_atoi(char *);
char *Convert_Number(long int, int, int);
void prnt_err(info_t *, char *);
void Remove_Comments(char *);

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


typedef struct liststring
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


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

int BuildHlist(info_t *information,char *buff, int linec);
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
