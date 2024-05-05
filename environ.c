#include "shell.h"

/**
* display_environment - Prints all environment variables.
* @ctx: Shell context that includes the environment list.
* Return: Always returns success status code.
*/
int display_environment(info_t *ctx)
{
	for (list_t *env_var = ctx->env; env_var; env_var = env_var->next)
	{
		printf("%s\n", env_var->str);
	}
	return (0);
}

/**
* find_environment_value - a specified environment variable.
* @ctx: Shell context including the environment list.
* @key: Environment variable name to search for.
* Return: Value associated with the environment variable, or NULL if not found.
*/
char *find_environment_value(info_t *ctx, const char *key)
{
	for (list_t *item = ctx->env; item; item = item->next)
	{
		if (strncmp(item->str, key, strlen(key)) == 0 &&
			item->str[strlen(key)] == '=')
			return (item->str + strlen(key) + 1);
	}
	return (NULL);
}

/**
* modify_environment - Modifies or creates an environment variable.
* @ctx: Shell context containing the environment and arguments.
* Return: Status code indicating success or failure.
*/
int modify_environment(info_t *ctx)
{
	if (ctx->argc != 3)
	{
		fprintf(stderr, "Usage error: incorrect arguments\n");
		return (1);
	}

	char *env_var = ctx->argv[1];

	char *value = ctx->argv[2];

	if (set_environment_var(ctx, env_var, value))
	{
		fprintf(stderr, "Failed to set %s\n", env_var);
		return (1);
	}
	return (0);
}

/**
* erase_environment_variable - Removes an environment variable.
* @ctx: Context containing the arguments for the operation.
* Return: Returns 0 if successful, 1 for failure.
*/
int erase_environment_variable(info_t *ctx)
{
	if (ctx->argc < 2)
	{
		fprintf(stderr, "Error: Insufficient arguments provided.\n");
		return (1);
	}

	for (int i = 1; i < ctx->argc; i++)

	{
		if (unset_environment_var(ctx, ctx->argv[i]))
		{
			fprintf(stderr, "Failed to unset %s\n", ctx->argv[i]);
		}
	}
	return (0);
}

/**
* populate_environment - Loads system environment into the shell's list.
* @ctx: Shell context to populate.
* Return: 0 on success, 1 on failure.
*/
int populate_environment(info_t *ctx)
{
	list_t *temp_list = NULL;

	for (int i = 0; environ[i]; i++)

	{
		if (!append_to_list(&temp_list, environ[i]))
		{
			fprintf(stderr, "Error populating environment list.\n");
			return (1);
		}
	}
	ctx->env = temp_list;
	return (0);
}
