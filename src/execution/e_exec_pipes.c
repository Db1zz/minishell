/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:03:59 by jroseiro          #+#    #+#             */
/*   Updated: 2024/11/28 13:14:04 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

static void	setup_pipe_fds(int index, int pipes[2][2], t_cmd *cmd)
{
	if (index > 0)
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[index][1], STDOUT_FILENO);
}

static void	close_child_pipes(int index, int pipes[2][2])
{
	while (index > 0)
	{
		close(pipes[index -1][0]);
		close(pipes[index][1]);
		index--;
	}
}

static void exec_piped_cmd(t_cmd *cmd, t_list *env, int index, int pipes[2][2])
{
	setup_pipe_fds(index, pipes, cmd);
	close_child_pipes(index, pipes);

	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd, env);
		exit(EXIT_SUCCESS);
	}
	execute_external(cmd, env);
	exit(EXIT_FAILURE);
}

int	exec_pipe_cmds(t_cmd *cmd_list, t_list *env, int pipes[2][2], int cmd_count)
{
	pid_t   pid;
    int     status;
    int     i;

    i = 0;
    while (i < cmd_count)
    {
        pid = fork();
        if (pid < 0)
        {
            close_pipes(cmd_count, pipes);
            return (EXIT_FAILURE);
        }
        if (pid == 0)
            exec_piped_cmd(cmd_list, env, i, pipes);
        cmd_list = cmd_list->next;
        i++;
    }
    i = 0;
    while (i++ < cmd_count)
        wait(&status);
    return (WEXITSTATUS(status));
}