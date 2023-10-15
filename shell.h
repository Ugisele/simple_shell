#ifndef _SHELL_H_
#define _SHELL_H_

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

/* read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_typ;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_typ *env;
	list_typ *history;
	list_typ *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_typ;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_typ *);
} builtin_table;

/* The_convert.c_file*/
int interactive(info_typ *);
int _atoi(char *);
int _isalpha(int);
int is_delim(char, char *);

/* The_variables.c_File */
int is_chain(info_typ *, char *, size_typ *);
void check_chain(info_typ *, char *, size_typ *, size_typ, size_typ);
int alias_replace(info_typ *);
int vars_replace(info_typ *);
int string_replace(char **, char *);

/* The_builtins.c_file */
int _myexit(info_typ *);
int _mycd(info_typ *);
int _myhelp(info_typ *);

/* The_memory.c_file */
int good(void **);

/* The_environment.c_file */
char *_getenv(info_typ *, const char *);
int _myenv(info_typ *);
int _mysetenv(info_typ *);
int _myunsetenv(info_typ *);
int populate_env_list(info_typ *);

/* The_get_environment.c */
char **get_environ(info_typ *);
int _unsetenv(info_typ *, char *);
int _setenv(info_typ *, char *, char *);

/* The_builtins0.c */
int _myhistory(info_typ *);
int _myalias(info_typ *);

/* The_reallocate.c */
char *_memoryset(char *, char, unsigned int);
void _ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* The_getinformation.c_file */
void clear_info(info_typ *);
void set_info(info_typ *, char **);
void free_info(info_typ *, int);

/* The_exist.c_file */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* The_erratum.c */
void _eputs(char *);
int _eputchar(char);
int _putfdir(char chr, int fdir);
int _putsfdir(char *str, int fdir);

/* The_erratum0.c */
int _erratoi(char *);
void print_error(info_typ *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*The_getdata.c_file*/
ssize_typ get_input(info_typ *);
int _getline(info_typ *, char **, size_typ *);
void sigintHandler(int);

/* The_analyzer.c */
int is_cmd(info_typ *, char *);
char *dup_chars(char *, int, int);
char *path_found(info_typ *, char *, char *);
#endif
