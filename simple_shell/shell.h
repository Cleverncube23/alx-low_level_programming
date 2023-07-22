#ifndef SHELL_H
#define SHELL_H

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

/* Read/write buffer sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining types */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Convert number options */
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
} list_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on, count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
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

/* Function prototypes */

/* toem_shloop.c */
int shell_loop(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void print_error(char *);
int print_char_error(char);
int print_char_to_fd(char c, int fd);
int print_str_to_fd(char *str, int fd);

/* toem_string.c */
int string_length(char *);
int compare_strings(char *, char *);
char *starts_with(const char *, const char *);
char *string_concat(char *, char *);

/* toem_string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int print_char(char);

/* toem_exits.c */
char *string_n_copy(char *, char *, int);
char *string_n_concat(char *, char *, int);
char *find_character(char *, char);

/* toem_tokenizer.c */
char **split_string(char *, char *);
char **split_string_advanced(char *, char);

/* toem_realloc.c */
char *memory_set(char *, char, unsigned int);
void free_string_array(char **);
void *resize_memory(void *, unsigned int, unsigned int);

/* toem_memory.c */
int free_buffer(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int convert_to_integer(char *);

/* toem_errors1.c */
int error_atoi(char *);
void print_error(info_t *, char *);
int print_digit(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int execute_exit(info_t *);
int execute_cd(info_t *);
int execute_help(info_t *);

/* toem_builtin1.c */
int execute_history(info_t *);
int execute_alias(info_t *);

/* toem_getline.c */
ssize_t get_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *get_environment(info_t *, const char *);
int execute_env(info_t *);
int execute_setenv(info_t *);
int execute_unsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int unset_environment(info_t *, char *);
int set_environment(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_length(const list_t *);
char **list_to_string_array(list_t *);
size_t print_list(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chaining(info_t *, char *, size_t *);
void check_chaining(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variables(info_t *);
int replace_string(char **, char *);

#endif
