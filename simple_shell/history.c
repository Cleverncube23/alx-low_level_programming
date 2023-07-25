#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */
char *get_history_file(info_t *info)
{
	char *dir = _getenv(info, "HOME=");
	if (!dir)
		return NULL;

	char *filename = malloc(_strlen(dir) + _strlen(HIST_FILE) + 2);
	if (!filename)
	{
		free(dir);
		return NULL;
	}

	_strcpy(filename, dir);
	_strcat(filename, "/");
	_strcat(filename, HIST_FILE);

	free(dir);
	return filename;
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	char *filename = get_history_file(info);
	if (!filename)
		return -1;

	ssize_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return -1;

	list_t *node = info->history;
	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);
	return 1;
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	char *filename = get_history_file(info);
	if (!filename)
		return 0;

	ssize_t fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return 0;

	struct stat st;
	if (!fstat(fd, &st) || st.st_size < 2)
	{
		close(fd);
		return 0;
	}

	char *buf = malloc(st.st_size + 1);
	if (!buf)
	{
		close(fd);
		return 0;
	}

	ssize_t rdlen = read(fd, buf, st.st_size);
	buf[st.st_size] = '\0';
	close(fd);

	if (rdlen <= 0)
	{
		free(buf);
		return 0;
	}

	int linecount = 0;
	char *p = buf;
	while (*p)
	{
		char *end = _strchr(p, '\n');
		if (end)
			*end = '\0';
		build_history_list(info, p, linecount++);
		if (end)
			p = end + 1;
		else
			break;
	}

	free(buf);
	info->histcount = linecount;
	while (info->histcount >= HIST_MAX)
	{
		delete_node_at_index(&(info->history), 0);
		info->histcount--;
	}
	renumber_history(info);
	return info->histcount;
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	add_node_end(&(info->history), buf, linecount);
	return 0;
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	int i = 0;
	list_t *node = info->history;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return info->histcount = i;
}
