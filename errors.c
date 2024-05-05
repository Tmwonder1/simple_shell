#include "shell.h"

/**
* output_error_string - outputs a string to stderr
* @msg: the message to be output
*
* Return: None
*/
void output_error_string(char *msg)
{
	int idx = 0;

	if (!msg)
		return;
	while (msg[idx] != '\0')
	{
		put_error_char(msg[idx]);
		idx++;
	}
}

/**
* put_error_char - sends a character to the standard error
* @ch: character to be sent
*
* Return: 1 if successful, -1 on error with errno set accordingly.
*/
int put_error_char(char ch)
{
	static int pos;

	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || pos >= WRITE_BUF_SIZE)
	{
		write(2, buffer, pos);
		pos = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[pos++] = ch;
	return (1);
}

/**
* put_char_to_fd - writes a character to a specified file descriptor
* @ch: the character to output
* @fd: file descriptor to which the char is written
*
* Return: 1 if successful, -1 on error with errno set.
*/
int put_char_to_fd(char ch, int fd)
{
	static int buffer_pos;

	static char output_buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || buffer_pos >= WRITE_BUF_SIZE)
	{
		write(fd, output_buffer, buffer_pos);
		buffer_pos = 0;
	}
	if (ch != BUF_FLUSH)
		output_buffer[buffer_pos++] = ch;
	return (1);
}

/**
* output_string_to_fd - outputs a string to a specified file descriptor
* @msg: the message to be output
* @fd: file descriptor to use
*
* Return: total number of characters written
*/
int output_string_to_fd(char *msg, int fd)
{
	int count = 0;

	if (!msg)
		return (0);
	while (*msg)
	{
		count += put_char_to_fd(*msg++, fd);
	}
	return (count);
}
