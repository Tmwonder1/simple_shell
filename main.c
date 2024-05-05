#include "shell.h"

/**
* main - Main entry point of the shell program.
* @argc: Argument count.
* @argv: Argument vector.
*
* Return: EXIT_SUCCESS on successful execution, EXIT_FAILURE on error.
*/
int main(int argc, char **argv)
{
	exec_info_t exec_info = EXEC_INFO_INIT; /* Initialize execution information */
	int file_descriptor = 2; /* Default to stderr */

	/* Inline assembly to manipulate file descriptor value */
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor));

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY); /* opening in argv[1] */
		if (file_descriptor == -1)
		{
			switch (errno)
			{
				case EACCES:
					exit(126); /* Exit with 126 if permission is denied */
				case ENOENT:
					print_error_string(argv[0]); /* Utility function to print errors */
					print_error_string(": 0: Can't open ");
					print_error_string(argv[1]);
					print_character_error('\n');
					exit(127); /* Exit with 127 if file not found */
			}
			return (EXIT_FAILURE);
		}
		exec_info.readfd = file_descriptor; /* file descriptor in exec_info */
	}

	/* Functions to initialize shell environment and read command history */
	load_environment_variables(&exec_info);
	load_history(&exec_info);

	/* Start the shell loop */
	shell_loop(&exec_info, argv);

	return (EXIT_SUCCESS);
}
