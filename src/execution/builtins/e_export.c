/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:17:13 by jroseiro          #+#    #+#             */
/*   Updated: 2024/10/29 20:41:32 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../e_execute.h"

/*
** is_valid_identifier - Checks if a name is a valid environment variable name
** Valid: [a-zA-Z_][a-zA-Z0-9_]*
** Examples:
** Valid: HOME, _PATH, var1
** Invalid: 1var, $HOME, var-name
*/

static int	is_valid_identifier(const char *str)
{
	int i;

	if (!str || !*str)
		return (0);
	
	// first char must be alpha or '_'
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);

	// rest can be letters, numbers or underscore
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
** find_env_var - Finds an environment variable in the list
** Returns pointer to the node containing the variable, or NULL if not found
*/
static t_list *find_env_var(t_list *env, const char *name)
{
	size_t	name_len;
	char	*equals;

	name_len = 0;
	while (name[name_len] && name[name_len] != '=')
		name_len++;
	
	while (env)
	{
		if (equals = !ft_strncmp(env->content, name, name_len)
			&& (equals - (char *)env->content) == (long)name_len)
	}
}


/*
** update_or_add_var - Updates existing var or adds new one
** Returns 0 on success, 1 on error
*/
static int update_or_add_var(t_list **env, char *var);

/*
** builtin_export - Implements the export command
** Without args: displays all environment variables in export format
**		export format meaning
**
** With args: adds/updates environment variables
*/

int builtin_export(char **args, t_list *env)
{
	int	i;
	int	status;
	t_list *current;

	// no args? Print all vars
	if (!args[1])
	{
		current = env;
		while (current)
		{
			printf("declare -x %s\n", (char *)current->content);
			current = current->next;
		}
		return (EXIT_SUCCESS);
	}

	// otherwise, process each arg
	status = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i])) // check for correct identifiers and change status if wrong result
		{
			ft_dprintf(STDERR_FILENO, MSG_EXPORT_ERROR, args[i]);
			status = EXIT_FAILURE;
		}
		else if (update_or_add_var(&env, args[i]) != EXIT_SUCCESS)
			status = EXIT_FAILURE;
		i++;
	}
	return (status);
}