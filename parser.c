#include "shell.h"
#include <sys/stat.h>

/**
* check_executable - Checks if a specified path points to an executable file.
* @info: Pointer to an info structure with environment and state.
* @filepath: Path to check for executable status.
* Return: Non-zero if executable, zero otherwise.
*/
int check_executable(info_t *info, char *filepath)
{
	struct stat file_stat;

	if (info == NULL || filepath == NULL || stat(filepath, &file_stat) != 0)
		return (0);

	return ((file_stat.st_mode & S_IFREG) != 0);
}

/**
* copy_segment - Copies a segment of a string into a static buffer.
* @src: Source string from which to copy.
* @begin: Start index within source string to start copying.
* @end: End index within source string to stop copying.
* Return: Pointer to the segment.
*/
char *copy_segment(char *src, int begin, int end)
{
	static char segment[1024];

	int j = 0;

	for (int i = begin; i < end && src[i] != ':'; i++)

		segment[j++] = src[i];
	segment[j] = '\0';
	return (segment);
}

/**
* resolve_command_path - for a command using PATH environment variable.
* @info: Pointer to an info structure containing command details.
* @path_env: PATH environment variable string.
* @command: Command to resolve path for.
* Return: Full path of command if found, NULL otherwise.
*/
char *resolve_command_path(info_t *info, char *path_env, char *command)
{
	if (path_env == NULL || command == NULL)
		return (NULL);

	if (_strlen(command) > 2 && starts_with(command, "./"))
	{
		if (check_executable(info, command))
			return (command);
	}

	char *full_path;

	int start = 0, i = 0;

	while (path_env[i] != '\0')
	{
		if (path_env[i] == ':' || path_env[i] == '\0')
		{
			full_path = copy_segment(path_env, start, i);
			if (_strlen(full_path) > 0)
				_strcat(full_path, "/");
			_strcat(full_path, command);

			if (check_executable(info, full_path))
				return (full_path);

			start = i + 1;
		}
		i++;
	}

	return (NULL);
}
