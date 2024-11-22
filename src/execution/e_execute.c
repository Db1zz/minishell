/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:12:47 by zrz               #+#    #+#             */
/*   Updated: 2024/11/22 22:00:03 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

static void	save_fds(int og_fds[2])
{
	og_fds[0] = dup(STDIN_FILENO);
	og_fds[1] = dup(STDOUT_FILENO);
}

static void	restore_fds(int og_fds[2])
{
	og_fds[0] = dup(STDIN_FILENO);
	og_fds[1] = dup(STDOUT_FILENO);
	close(og_fds[0]);
	close(og_fds[1]);
}

/*
**	main entry point for command execution,
**	which then delegates to either builtin or external command handling.
*/
int execute_cmd(t_cmd *cmd, t_list *env)
{
	int	og_fds[2];
	int	status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (EXIT_SUCCESS);

	save_fds(og_fds);

	if (cmd->redirections)
	{
		status = setup_redirections(cmd->redirections);
		if (status != EXIT_SUCCESS)
		{
			restore_fds(og_fds);
			return (status);
		}
	}

	if (is_builtin(cmd->args[0]))
		status = execute_builtin(cmd,env);
	else
		status = execute_external(cmd, env);

	restore_fds(og_fds);
	return (status);
}

