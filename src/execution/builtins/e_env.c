/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:21:03 by jroseiro          #+#    #+#             */
/*   Updated: 2024/10/28 20:33:24 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../e_execute.h"

/*
** builtin_env - Implements the env command
** No options or arguments supported
** Just prints all environment variables
**
** Expected behavior:
** env          -> prints all environment variables
** env arg      -> error: too many arguments
*/

int	builtin_env(char **args, t_list *env)
{
	t_list *current;

	// check for args (not supported)
	if (args[1])
	{
		ft_dprintf(STDERR_FILENO, MSG_ENV_ERROR, "too many arguments");
		return (EXIT_FAILURE);
	}

	// Go trhoguh env list
	current = env;
	while (current)
	{
		// only print if it contains '=' (actual env vars)
		if (ft_strchr(current->content, '='))
			printf("%s\n", (char *)current->content);
		current = current->next; // move to the next
	}

	return (EXIT_SUCCESS);
}