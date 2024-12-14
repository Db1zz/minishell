/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 23:26:48 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 14:24:56 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_builtins.h"

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
