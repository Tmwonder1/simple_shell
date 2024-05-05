#include "shell.h"

/**
* get_environ - Retrieves a string array copy of the environment.
* @info: Structure containing potential arguments and environment details.
* Return: Pointer to environment string array.
*/
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
* _unsetenv - Removes an environment variable.
* @info: Structure containing potential arguments and environment details.
* @var: The name of the environment variable to remove.
* Return: 1 if the environment was changed (variable deleted), 0 otherwise.
*/
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *position;

	if (!node || !var)
	{
		return (0);
	}

	while (node)
	{
		position = starts_with(node->str, var);
		if (position && *position == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			/* Reset to start after modification */
			node = info->env;
			index = 0;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
* _setenv - Initializes or modifies an environment variable.
* @info: Structure containing potential arguments and environment details.
* @var: The name of the environment variable.
* @value: The value to set for the environment variable.
* Return: 0 on success, 1 on error (e.g., allocation failure).
*/
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer;

	list_t *node;
	char *position;

	if (!var || !value)
	{
		return (0);
	}

	buffer = malloc(_strlen(var) + _strlen(value) + 2);  /* +2 for '=' and '\0' */
	if (!buffer)
	{
		return (1);
	}

	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);

	for (node = info->env; node; node = node->next)
	{
		position = starts_with(node->str, var);
		if (position && *position == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
	}

	/*Variable not found, add new */
	add_node_end(&(info->env), buffer, 0);
	free(buffer);  /* Free buffer after adding because list holds the copy */
	info->env_changed = 1;
	return (0);
}
