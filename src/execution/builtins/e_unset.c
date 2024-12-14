/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:17:21 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 01:32:18 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../e_execute.h"

// TODO:

/*
** a "checker":
**
** is_valid_identifier - Checks if name is a valid environment variable name
** Same rules as export: [a-zA-Z_][a-zA-Z0-9_]*
*/

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
** A function to do the actual removing / 'unseting'
**
** remove_env_var - Removes variable from environment list if found
** Returns EXIT_SUCCESS even if variable wasn't found (bash behavior)
*/

static int	remove_env_var(t_env *env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = env;
	while (current)
	{
		while (current)
		{
			if (ft_strcmp(current->key, key) == 0)
			{
				if (prev)
					prev->next = current->next;
				(free(current->key), free(current->value), free(current));
				return (free(current->key), free(current), EXIT_SUCCESS);
			}
			prev = current;
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}

/*
** A mini 'main' function to manage it all:
**
** builtin_unset - Implements the unset command
** Removes variables from environment
** Returns 0 on success, 1 if any argument is invalid
*/

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;
	int	status;

	if (!args[1])
		return (EXIT_SUCCESS);
	status = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_dprintf(STDERR_FILENO, MSG_UNSET_ERROR, args[i]);
			status = EXIT_FAILURE;
		}
		else
			remove_env_var(shell->env, args[i]);
		i++;
	}
	return (status);
}
