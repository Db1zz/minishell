/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:21:03 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 17:07:54 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_builtins.h"
#include "env.h"

/*
** builtin_env - Implements the env command
** No options or arguments supported
** Just prints all environment variables
**
** Expected behavior:
** env          -> prints all environment variables
** env arg      -> error: too many arguments
*/

int	builtin_env(char **args, t_shell *shell)
{
	if (args[1])
	{
		ft_dprintf(STDERR_FILENO, MSG_ENV_ERROR, "too many arguments");
		return (EXIT_NOT_FOUND);
	}
	print_env(shell->env);
	return (EXIT_SUCCESS);
}
