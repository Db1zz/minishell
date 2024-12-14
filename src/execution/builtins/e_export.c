/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 23:26:48 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 02:05:03 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "e_execute.h"
#include "env.h"

int	builtin_export(char **args, t_shell *shell)
{
	t_env	*env;
	int		status;
	int		i;

	env = shell->env;
	i = 0;
	if (!args[1])
	{
		print_sorted_env(shell->env);
		return (EXIT_SUCCESS);
	}
	while (args[i])
	{
	}
}
