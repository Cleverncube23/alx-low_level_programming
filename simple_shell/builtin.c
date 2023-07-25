#include "shell.h"

/**
 * _myexit - Exits the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Exits with a given exit status (-2) if info->argv[0] == "exit" and
 *         there is an exit argument, otherwise returns -1.
 */
int _myexit(info_t *info)
{
    int exitcheck;

    if (info->argv[1]) /* If there is an exit argument */
    {
        exitcheck = _erratoi(info->argv[1]);
        if (exitcheck == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return (1);
        }
        info->err_num = _erratoi(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * _mycd - Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (0);
        }
        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);

    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * _myhelp - Displays help information for the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); /* temp att_unused workaround */
    return (0);
}

/**
 * my_exit - Exits the shell.
 *
 * Return: Always returns 0 to indicate the shell should exit.
 */
int my_exit(void)
{
    printf("Exiting shell...\n");
    return 0;
}

/**
 * my_env - Print the current environment variables.
 *
 * Return: Always returns 0.
 */
int my_env(void)
{
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}

/**
 * my_setenv - Initialize a new environment variable or modify an existing one.
 * @name: Name of the environment variable.
 * @value: Value to be assigned to the environment variable.
 * @overwrite: Flag to determine if the variable should be overwritten if it exists.
 *
 * Return: 0 on success, -1 on failure.
 */
int my_setenv(const char *name, const char *value, int overwrite)
{
    if (overwrite || getenv(name) == NULL)
        return setenv(name, value, 1);
    else
        return 0;
}

/**
 * my_unsetenv - Remove an environment variable.
 * @name: Name of the environment variable to be removed.
 *
 * Return: 0 on success, -1 on failure.
 */
int my_unsetenv(const char *name)
{
    return unsetenv(name);
}

/**
 * my_cd - Change the current directory of the process.
 * @path: Path to the directory to change to. If NULL, change to the home directory.
 *
 * Return: 0 on success, -1 on failure.
 */
int my_cd(const char *path)
{
    char *dir = NULL;
    char cwd[1024];

    if (path == NULL)
    {
        dir = getenv("HOME");
        if (dir == NULL)
        {
            fprintf(stderr, "cd: No HOME environment variable.\n");
            return -1;
        }
    }
    else if (strcmp(path, "-") == 0)
    {
        dir = getenv("OLDPWD");
        if (dir == NULL)
        {
            fprintf(stderr, "cd: OLDPWD not set.\n");
            return -1;
        }
    }
    else
    {
        dir = (char *)path;
    }

    if (chdir(dir) == -1)
    {
        perror("cd");
        return -1;
    }

    getcwd(cwd, sizeof(cwd));
    setenv("OLDPWD", getenv("PWD"), 1);
    setenv("PWD", cwd, 1);

    return 0;
}
