#include "shell.h"

/**
* display_history - Outputs the commands previously entered into the shell.
* @context: Shell context containing the history list.
* Return: Always 0 to indicate successful execution.
*/
int display_history(info_t *context)
{
	list_t *current = context->history;

	while (current)
	{
		printf("%d %s\n", current->num, current->str);
		current = current->next;
	}
	return (0);
}

/**
* remove_alias - Deletes a specified alias from the list.
* @context: Shell context including aliases.
* @alias_name: Name of the alias to delete.
* Return: 0 if successful, 1 if alias not found.
*/
int remove_alias(info_t *context, char *alias_name)
{
	int index = 0;

	list_t *alias = find_alias(context->alias, alias_name);

	if (!alias)

	{
		return (1);
	}


	index = get_node_index(context->alias, alias);
	return (delete_node_at_index(&(context->alias), index) == NULL);
}

/**
* assign_alias - Assigns or updates an alias in the shell.
* @context: Shell context including aliases.
* @alias_definition: Alias definition in the form "name=value".
* Return: 0 on success, 1 on failure.
*/
int assign_alias(info_t *context, char *alias_definition)
{
	char *value_position = strchr(alias_definition, '=');

	if (!value_position || !*(value_position + 1))
		return (remove_alias(context, alias_definition));

	remove_alias(context, alias_definition); /*Remove existing alias if present */
	return (append_alias(&(context->alias), alias_definition) == NULL);
}

/**
* output_alias - Displays a single alias in a formatted manner.
* @node: The alias node to display.
* Return: 0 on success, 1 if the node is NULL.
*/
int output_alias(list_t *node)
{
	if (node && strchr(node->str, '='))
	{
		printf("alias %s='%s'\n", node->str, strchr(node->str, '=') + 1);
		return (0);
	}
	return (1);
}

/**
* manage_aliases - functionality, similar to the alias builtin command.
* @context: Shell context containing arguments and alias list.
* Return: Always returns 0 to conform to shell builtin structure.
*/
int manage_aliases(info_t *context)
{
	if (context->argc == 1)  /* If no specific alias is requested, print all. */
	{
		for (list_t *current = context->alias; current; current = current->next)
			output_alias(current);
	}
	else  /* Set or print specific aliases */
	{
		for (int i = 1; context->argv[i]; i++)

		{
			if (strchr(context->argv[i], '='))
				assign_alias(context, context->argv[i]);
			else
				output_alias(find_alias(context->alias, context->argv[i]));
		}
	}
	return (0);
}
