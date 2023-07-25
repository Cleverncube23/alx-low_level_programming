#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	return (path && !stat(path, &st) && S_ISREG(st.st_mode));
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char buf[1024];

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			if (curr_pos > 0)
				_snprintf(buf, sizeof(buf), "%.*s/%s", i - curr_pos, pathstr + curr_pos, cmd);
			else
				_snprintf(buf, sizeof(buf), "%s", cmd);

			if (is_cmd(info, buf))
				return (_strdup(buf));

			if (!pathstr[i])
				break;

			curr_pos = i + 1;
		}

		i++;
	}
	return (NULL);
}
