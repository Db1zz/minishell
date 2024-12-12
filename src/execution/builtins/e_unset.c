/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:17:21 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/12 18:10:46 by jroseiro         ###   ########.fr       */
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
	int i;

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

static int	remove_env_var(t_list *env, const char *name)
{
	t_list	*current;
	t_list	*prev;
	char	*equals;
	size_t	name_len;

	name_len = ft_strlen(name);
	prev = NULL;
	current = env;
	while (current)
	{
		    while (current)
		{
			equals = ft_strchr(current->content, '=');
			if (equals && !ft_strncmp(current->content, name, name_len)
				&& ((char *)current->content)[name_len] == '=')
			{
				if (prev)
					prev->next = current->next;
				free(current->content);
				free(current);
				return (EXIT_SUCCESS);
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

int	builtin_unset(char **args, t_list *env)
{
	int	i;
	int	status;

	if (!args[1]) // if there is nothing to remove / its already gone, it succeeds
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
			remove_env_var(env, args[i]);
		i++;
	}
	return(status);
}
