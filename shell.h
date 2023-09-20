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

/*functios to find the path*/
char *Chars_Dup(char *, int, int);
int is_it_cmd(info_t *, char *);
char *Path_Find(info_t *, char *, char *);


