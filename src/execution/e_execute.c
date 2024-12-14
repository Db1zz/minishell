/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:12:47 by zrz               #+#    #+#             */
/*   Updated: 2024/12/14 16:48:02 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"
#include "minishell.h"

static void	save_fds(int og_fds[2])
{
	og_fds[0] = dup(STDIN_FILENO);
	og_fds[1] = dup(STDOUT_FILENO);
}

static void	restore_fds(int og_fds[2])
{
	dup2(og_fds[0], STDIN_FILENO);
	dup2(og_fds[1], STDOUT_FILENO);
	close(og_fds[0]);
	close(og_fds[1]);
}

/*
**	main entry point for command execution,
**	which then delegates to either builtin or external command handling.
*/
int	execute_cmd(t_shell *shell)
{
	int		og_fds[2];
	int		status;
	t_cmd	*cmd;

	cmd = shell->cmds;
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
	if (cmd->next)
		status = execute_pipeline(shell);
	else if (is_builtin(cmd->args[0]))
		status = execute_builtin(cmd, shell);
	else
		status = execute_external(cmd, shell);
	restore_fds(og_fds);
	return (status);
}
