#include "shell.h"

/**
* copy_n_characters -  of characters from one string to another.
* @destination: Pointer to the destination string.
* @source: Pointer to the source string.
* @count: Number of characters to copy.
* Return: Pointer to the destination string.
*/
char *copy_n_characters(char *destination, char *source, int count)
{
	int index = 0, pad_index;

	char *dest_start = destination;

	/* Copy characters from source to destination until null character or limit */
	while (source[index] != '\0' && index < count - 1)
	{
		destination[index] = source[index];
		index++;
	}

	/* If limit is not reached, pad the rest with null characters */
	if (index < count)
	{
		for (pad_index = index; pad_index < count; pad_index++)
			destination[pad_index] = '\0';
	}
	return (dest_start);
}

/**
* concatenate_n_characters - Codestination string.
* @destination: Pointer to the destination string.
* @source: Pointer to the source string.
* @count: Maximum number of characters to append.
* Return: Pointer to the concatenated string.
*/
char *concatenate_n_characters(char *destination, char *source, int count)
{
	int dest_len = 0, src_index = 0;

	char *dest_start = destination;

	/* Move to the end of the destination string */
	while (destination[dest_len] != '\0')
		dest_len++;

	/* Append characters from source to destination */
	while (source[src_index] != '\0' && src_index < count)
	{
		destination[dest_len++] = source[src_index++];
	}

	/* Ensure the string is null-terminated */
	destination[dest_len] = '\0';

	return (dest_start);
}

/**
* find_character - Searches for the first occurrence character in the string.
* @string: The string to search.
* @character: The character to find.
* Return: Pointer to the found character in the string, or NULL if not found.
*/
char *find_character(char *string, char character)
{
	while (*string != '\0')
	{
		if (*string == character)
			return (string);
		string++;
	}
	return (NULL);  /* Character not found */
}
