#include "shell.h"

/**
* quit_shell - Exits the shell with a status if specified.
* @shell_info: Context with optional exit status.
* Return: -2 to halt, 1 if error in provided status.
*/
int quit_shell(info_t *shell_info)
{
	int status_code;

	if (shell_info->argv[1])  /* Check for a specific exit code */
	{
		status_code = string_to_int(shell_info->argv[1]);
		if (status_code == -1)  /* Handling non-integer input */
		{
			shell_info->status = 2;
			shell_error(shell_info, "Error: Illegal number provided: ");
			quick_print(shell_info->argv[1]);
			quick_char('\n');
			return (1);
		}
		shell_info->err_num = status_code;
		return (-2);
	}
	shell_info->err_num = -1;
	return (-2);
}

/**
* change_directory - Modifies the process's working directory.
* @shell_info: Context containing directory arguments.
* Return: Always returns 0, indicates error if change fails.
*/
int change_directory(info_t *shell_info)
{
	char *current_dir, *target_dir, dir_buffer[1024];

	int result;

	current_dir = getcwd(dir_buffer, sizeof(dir_buffer));
	if (!current_dir)
		display_message("Error: Unable to retrieve current directory.\n");

	if (!shell_info->argv[1])
	{
		target_dir = fetch_env(shell_info, "HOME=");
		result = chdir(target_dir ? target_dir : "/");
	}
	else if (compare_strings(shell_info->argv[1], "-") == 0)
	{
		target_dir = fetch_env(shell_info, "OLDPWD=");
		display_path(target_dir ? target_dir : current_dir);
		result = chdir(target_dir ? target_dir : "/");
	}
	else
	{
		result = chdir(shell_info->argv[1]);
	}

	if (result == -1)
	{
		shell_error(shell_info, "Error: cannot change directory to ");
		quick_print(shell_info->argv[1]), quick_char('\n');
	}
	else
	{
		update_env(shell_info, "OLDPWD", current_dir);
		update_env(shell_info, "PWD", getcwd(dir_buffer, sizeof(dir_buffer)));
	}
	return (0);
}

/**
* display_help - Provides help information for shell commands.
* @shell_info: Contains the arguments, if any.
* Return: Always returns 0.
*/
int display_help(info_t *shell_info)
{
	display_message("Help is on the way! Functionality pending.\n");
	if (shell_info->argv[0])  /* Utilize potential unused variable */
		;
	return (0);
}
