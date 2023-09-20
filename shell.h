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

