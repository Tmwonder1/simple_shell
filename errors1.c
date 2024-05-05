#include "shell.h"

/**
* string_to_int - safely converts a string to an integer
* @str: the string to convert
* Return: 0 if no digits found,value, -1 on overflow or non-digit character
*/
int string_to_int(char *str)
{
	int idx = 0;

	unsigned long int accum = 0;

	if (*str == '+')
		str++;  /* Skip leading plus sign if present */
	for (; str[idx] != '\0'; idx++)
	{
		if (str[idx] >= '0' && str[idx] <= '9')
		{
			accum = accum * 10 + (str[idx] - '0');
			if (accum > INT_MAX)
				return (-1);  /* Overflow handling */
		}
		else
			return (-1);  /* Non-digit character */
	}
	return (accum);
}

/**
* display_error - displays an error message using structured information
* @context: the info struct containing execution context
* @error_msg: message describing the error
*/
void display_error(info_t *context, char *error_msg)
{
	_eputs(context->fname);
	_eputs(": ");
	print_dec(context->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(context->argv[0]);
	_eputs(": ");
	_eputs(error_msg);
}

/**
* print_dec - outputs a decimal number to a specified file descriptor
* @number: the number to print
* @fd: the file descriptor to write to
*
* Return: the number of characters printed
*/
int print_dec(int number, int fd)
{
	int (*selected_put)(char) = _putchar;
	int digits, char_count = 0;

	unsigned int abs_val, current_val;

	if (fd == STDERR_FILENO)
		selected_put = _eputchar;
	if (number < 0)
	{
		abs_val = -number;
		selected_put('-');
		char_count++;
	}
	else
		abs_val = number;

	current_val = abs_val;
	for (digits = 1000000000; digits > 1; digits /= 10)
	{
		if (abs_val / digits)
		{
			selected_put('0' + current_val / digits);
			char_count++;
		}
		current_val %= digits;
	}
	selected_put('0' + current_val);
	char_count++;

	return (char_count);
}

/**
* itoa_clone - custom implementation of integer to string conversion
* @value: the number to convert
* @base: numerical base for conversion
* @options: formatting options
*
* Return: pointer to the resulting null-terminated string
*/
char *itoa_clone(long int value, int base, int options)
{
	static char *digits;

	static char buffer[50];

	char is_negative = 0;

	char *ptr;

	unsigned long num = value;

	if (!(options & CONVERT_UNSIGNED) && value < 0)
	{
		num = -value;
		is_negative = '-';

	}
	digits = options & CONVERT_LOWERCASE ? "0123456789abcdef"
										 : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = digits[num % base];
		num /= base;
	} while (num != 0);

	if (is_negative)
		*--ptr = is_negative;
	return (ptr);
}

/**
* skip_comments - nullifies comments starting with '#' in a string
* @line: pointer to the string to process
*
* Return: Nothing;
*/
void skip_comments(char *line)
{
	int idx;

	for (idx = 0; line[idx] != '\0'; idx++)
		if (line[idx] == '#' && (!idx || line[idx - 1] == ' '))
		{
			line[idx] = '\0';
			break;
		}
}
