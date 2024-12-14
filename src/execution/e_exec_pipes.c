/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:03:59 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 17:07:43 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

static void	setup_pipe(int index, int pipes[][2], t_cmd *cmd)
{
	if (index > 0)
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[index][1], STDOUT_FILENO);
}

static void	close_unused_pipes(int index, int pipes[][2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (i != index - 1)
			close(pipes[i][0]);
		if (i != index)
			close(pipes[i][1]);
		i++;
	}
}

static void	close_all_pipes(int pipes[][2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static int	setup_pipes_and_redirections(int index, int pipes[][2],
		int cmd_count, t_cmd *cmd_list)
{
	int	status;

	status = EXIT_SUCCESS;
	setup_pipe(index, pipes, cmd_list);
	close_unused_pipes(index, pipes, cmd_count);
	if (cmd_list->redirections)
	{
		status = setup_redirections(cmd_list->redirections);
		if (status != EXIT_SUCCESS)
			exit(status);
	}
	return (status);
}

int	exec_pipeline_routine(t_shell *shell, int pipes[][2], int cmd_count)
{
	pid_t	pid;
	int		status;
	int		i;
	t_cmd	*cmd_list;

	i = 0;
	cmd_list = shell->cmds;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			status = setup_pipes_and_redirections(i, pipes,
					cmd_count, cmd_list);
			if (is_builtin(cmd_list->args[0]))
				exit(execute_builtin(cmd_list, shell));
			exit(execute_external(cmd_list, shell));
		}
		cmd_list = cmd_list->next;
		i++;
	}
	close_all_pipes(pipes, cmd_count);
	while (cmd_count-- > 0)
		waitpid(-1, &status, 0);
	return (WEXITSTATUS(status));
}
