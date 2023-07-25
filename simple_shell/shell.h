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
#include <dirent.h>

/* for read/write buffers */
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

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
} list_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @environ: custom modified copy of environ from LL env
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Shell functions */
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* Helper functions */
char *find_path(info_t *info, char *pathstr, char *cmd);
char *dup_chars(char *pathstr, int start, int stop);
int is_cmd(info_t *info, char *path);
void populate_env_list(info_t *info);
void read_history(info_t *info);
void write_history(info_t *info);
void free_info(info_t *info, int status);
void clear_info(info_t *info);
char *_getenv(info_t *info, char *var);

/* String functions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* Memory functions */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* Input/output functions */
void _puts(char *str);
int _putchar(char c);

/* Tokenization and parsing */
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

/* Conversion and checks */
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);

/* Errors and printing */
void _eputs(char *str);
int _eputchar(char c);
void _putfd(char c, int fd);
void _putsfd(char *str, int fd);
int _erratoi(char *str);
void print_error(info_t *info, char *message);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *str);

/* Built-in commands */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int _myhistory(info_t *info);
int _myalias(info_t *info);

/* Additional helper functions */
ssize_t get_input(info_t *info);
int _getline(info_t *info, char **lineptr, size_t *n);
void sigintHandler(int sig_num);
int bfree(void **ptr);

/* Environment related functions */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *name);
int _setenv(info_t *info, char *name, char *value);

/* History related functions */
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Linked list functions */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head);

/* Alias related functions */
int replace_alias(info_t *info);

/* Variable related functions */
int replace_vars(info_t *info);
int replace_string(char **str, char *var);

#endif /* _SHELL_H_ */
