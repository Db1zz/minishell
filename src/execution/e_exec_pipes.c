/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:03:59 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/11 21:41:31 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

// static void	setup_pipe_fds(int index, int pipes[][2], t_cmd *cmd)
// {
// 	/*
// 		ls | ls | ls | ls
// 		0
// 		index == 0

// 		we need to open child and get the input from it connected to a second child
// 		instead of working on main processes
// 	*/
// 	if (index > 0)
// 		dup2(pipes[index - 1][0], STDIN_FILENO);
// 	if (cmd->next)
// 		dup2(pipes[index][1], STDOUT_FILENO);
// }

// static void	close_child_pipes(int index, int pipes[][2], int cmd_count)
// {
//     int i;

//     i = 0;
//     while (i < cmd_count - 1)
//     {
//         if (i != index - 1)
//             close(pipes[i][0]);
//         if (i != index)
//             close(pipes[i][1]);
//         i++;
//     }
// }

// static void exec_piped_cmd(t_cmd *cmd, t_list *env, int index, int pipes[][2])
// {
// 	int cmd_count;
// 	int	child_status;

// 	cmd_count = 0;
// 	t_cmd *tmp;

// 	tmp = cmd;
	
// 	while (tmp)
// 	{
// 		cmd_count++;
// 		tmp = tmp->next;
// 	}

// 	setup_pipe_fds(index, pipes, cmd);
// 	close_child_pipes(index, pipes, cmd_count);
// 	if (is_builtin(cmd->args[0]))
// 	{
// 		execute_builtin(cmd, env);
// 		exit(EXIT_SUCCESS);
// 	}
// 	child_status = execute_external(cmd, env);
// 	exit(child_status);
// }

// int	exec_pipe_cmds(t_cmd *cmd_list, t_list *env, int pipes[][2], int cmd_count)
// {
// 	pid_t   pid;
//     int     status;
//     int     i;

//     i = 0;
//     while (i < cmd_count)
//     {
//         pid = fork();
//         if (pid < 0)
//         {
//             close_pipes(cmd_count, pipes);
//             return (EXIT_FAILURE);
//         }
//         if (pid == 0)
//             exec_piped_cmd(cmd_list, env, i, pipes);
// 		if (pid > 0)
// 			close(pipes[i - 1][0]); // close read end of previous pipe
// 		if (i < cmd_count -1)
// 			close(pipes[i][1]); // close write end of current pipe
//         cmd_list = cmd_list->next;
//         i++;
//     }
//     while (i-- > 0)
// 	{
// 		waitpid(-1, &status, 0);
// 		printf("FINISHED: %d\n", i);	
// 	}
//     return (WEXITSTATUS(status));
// }






static void setup_pipe(int index, int pipes[][2], t_cmd *cmd) {
	if (index > 0)
		dup2(pipes[index - 1][0], STDIN_FILENO); // Input from previous pipe
	if (cmd->next)
		dup2(pipes[index][1], STDOUT_FILENO); // Output to next pipe
}

static void close_unused_pipes(int index, int pipes[][2], int cmd_count) {
	int i = 0;
	while (i < cmd_count - 1) {
		if (i != index - 1)
			close(pipes[i][0]); // Close read end
		if (i != index)
			close(pipes[i][1]); // Close write end
		i++;
	}
}

static void close_all_pipes(int pipes[][2], int cmd_count) {
	int i = 0;
	while (i < cmd_count - 1) {
		close(pipes[i][0]); // Close read end
		close(pipes[i][1]); // Close write end
		i++;
	}
}

int exec_pipe_cmds(t_cmd *cmd_list, t_list *env, int pipes[][2], int cmd_count)
{
	pid_t pid;
	int status;
	int i;
	
	i = 0;
	while (i < cmd_count) 
	{
		if ((pid = fork()) == 0) // Child process
		{ 
			setup_pipe(i, pipes, cmd_list);
			close_unused_pipes(i, pipes, cmd_count);
			if (cmd_list->redirections)
			{
				status = setup_redirections(cmd_list->redirections);
				if (status != EXIT_SUCCESS)
					exit(status);
			}
			if (is_builtin(cmd_list->args[0]))
				execute_builtin(cmd_list, env);
			exit(execute_external(cmd_list, env));
		}
		cmd_list = cmd_list->next; // Move to next command
		i++;
	}
	close_all_pipes(pipes, cmd_count); // Parent closes all pipes
	while (cmd_count-- > 0) // Wait for all children
		waitpid(-1, &status, 0);
	return WEXITSTATUS(status);
}
