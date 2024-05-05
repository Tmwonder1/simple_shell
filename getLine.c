#include "shell.h"
#include <signal.h>

/**
* fetch_input_buffer - Manages input buffering and history updates.
* @info: Structure containing shell info.
* @buffer: Reference to the command buffer.
* @buffer_size: Reference to the buffer size variable.
*
* Return: Number of bytes read, or 0 if buffer was not updated.
*/
ssize_t fetch_input_buffer(info_t *info, char **buffer, size_t *buffer_size)
{
	ssize_t num_read = 0;
	size_t new_size = 0;

	if (!*buffer_size)  /* Only refill if buffer is empty */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		num_read = getline(buffer, &new_size, stdin);
#else
		num_read = custom_getline(info, buffer, &new_size);
#endif
		if (num_read > 0 && (*buffer)[num_read - 1] == '\n')
		{
			(*buffer)[num_read - 1] = '\0';  /* Strip newline */
			num_read--;
		}

		if (num_read > 0)
		{
			info->linecount_flag = 1;
			strip_comments(*buffer);
			update_history(info, *buffer, info->histcount++);
			*buffer_size = num_read;
			info->cmd_buf = buffer;
		}
	}
	return (num_read);
}

/**
* extract_command - Parses from a buffer handling command chaining.
* @info: Shell info structure.
* @buffer: Command buffer.
* @start: Start position in buffer.
* @length: Total length of buffer.
*
* Return: Length of the extracted command.
*/
ssize_t extract_command(info_t *info, char *buffer,

						size_t start, size_t length)
{
	size_t pos = start;
	char *command_start = buffer + start;

	while (pos < length)
	{
		if (buffer[pos] == ';')  /* Detect command chain delimiter */
		{
			buffer[pos] = '\0';  /* Terminate current command */
			info->cmd_buf_type = detect_command_type(buffer, pos);
			break;
		}
		pos++;
	}

	info->arg = command_start;  /* Update command pointer */
	return (_strlen(command_start));  /* Return length of current command */
}

/**
* custom_getline - Custom method to read a line of input.
* @info: Structure containing shell info.
* @buffer_ref: Pointer to buffer.
* @size_ref: Reference to size of buffer.
*
* Return: Length of the read line, or -1 on failure.
*/
int custom_getline(info_t *info, char **buffer_ref, size_t *size_ref)
{
	static char local_buffer[READ_BUF_SIZE];

	char *temp_buffer;

	size_t temp_size = 0, read_size;
	ssize_t total_read = 0;

	/* Read input into a static local buffer */
	total_read = buffer_read(info, local_buffer, &temp_size);
	if (total_read <= 0)
	{
		return (-1);  /* Handle read failure or EOF */
	}

	temp_buffer = _realloc(*buffer_ref, *size_ref, *size_ref + temp_size + 1);
	if (!temp_buffer)
	{
		return (-1);
	}
	memcpy(temp_buffer + *size_ref, local_buffer, temp_size);
	temp_buffer[*size_ref + temp_size] = '\0';  /* Null-terminate */
	*buffer_ref = temp_buffer;
	*size_ref += temp_size;

	return (temp_size);
}

/**
* handle_sigint - Custom SIGINT handler to ignore Ctrl-C.
* @signal_num: Signal number, unused.
*/
void handle_sigint(int signal_num)
{
	_puts("\n$ ");
	_putchar(BUF_FLUSH);  /* Flush buffered output */
}
