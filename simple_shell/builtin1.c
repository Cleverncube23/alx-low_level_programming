#include "shell.h"

/**
 * _myhistory - Displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - Sets alias to string.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(info->alias),
                               get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_alias - Sets alias to string.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @alias: The alias string to print.
 */
void print_alias(char *alias)
{
    char *p = _strchr(alias, '=');

    if (p)
    {
        for (char *a = alias; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
    }
}

/**
 * _myalias - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
    char *p;

    if (info->argc == 1)
    {
        list_t *node = info->alias;
        while (node)
        {
            print_alias(node->str);
            node = node->next;
        }
    }
    else
    {
        for (int i = 1; info->argv[i]; i++)
        {
            p = _strchr(info->argv[i], '=');
            if (p)
                set_alias(info, info->argv[i]);
            else
                print_alias(node_starts_with(info->alias, info->argv[i], '='));
        }
    }

    return (0);
}
