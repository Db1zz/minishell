/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:45:36 by zrz               #+#    #+#             */
/*   Updated: 2024/12/13 17:33:57 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

static int	count_cmds(t_cmd *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

void	close_pipes(int cmd_count, int pipes[][2])
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

static int	create_pipes(int cmd_count, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) < 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	execute_pipeline(t_shell *shell)
{
	int	cmd_count;
	int	pipes[1024][2];
	int	status;

	cmd_count = count_cmds(shell->cmds);
	if (cmd_count == 1)
		return (execute_cmd(shell));
	if (create_pipes(cmd_count, pipes) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	status = exec_pipeline_routine(shell, pipes, cmd_count);
	close_pipes(cmd_count, pipes);
	return (status);
}
