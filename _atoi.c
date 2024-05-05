#include "shell.h"

/**
* check_interactive_mode - Checks if the shell is running in interactive mode
* @info: Pointer to the  the shell's execution context
*
* Description: Determines interactivity by checking if stdin is a terminal and
*              is among the standard file descriptors (0, 1, 2).
* Return: Non-zero if in interactive mode, zero otherwise.
*/
int check_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* char_is_delimiter - Verifies if a character belongs to a set of delimiters
* @character: Character to verify
* @delimiters: String representing all possible delimiter characters
*
* Description: Evaluates whether the given elimiters string.
* Return: True (1) if it is a delimiter, False (0) otherwise.
*/
int char_is_delimiter(char character, char *delimiters)
{
	while (*delimiters)
	{
		if (*delimiters++ == character)
			return (1);
	}
	return (0);
}

/**
* alpha_check - Determines if a character is an alphabetic letter
* @character: Character to evaluate
*
* Description: mine if the character is within alphabetic range.
* Return: True (1) if alphabetic, False (0) otherwise.
*/
int alpha_check(int character)
{
	return ((character >= 'a' && character <= 'z') ||
			(character >= 'A' && character <= 'Z'));
}

/**
* string_to_integer - Parses a string to derive an integer
* @str: String to convert to an integer
*
* Description: ng to construct an integer. Considers negative signs.
* Return:  by the string, or 0 if no numeric characters are present.
*/
int string_to_integer(char *str)
{
	int idx = 0, sign = 1, has_numeric = 0;

	unsigned int numeric_value = 0;

	while (str[idx] != '\0')
	{
		if (str[idx] == '-')
			sign = -sign;
		else if (str[idx] >= '0' && str[idx] <= '9')
		{
			has_numeric = 1;
			numeric_value = numeric_value * 10 + (str[idx] - '0');
		}
		else if (has_numeric)
			break;  /* Stop on first non-numeric after number begins */
		idx++;
	}
	return (sign * numeric_value);
}
