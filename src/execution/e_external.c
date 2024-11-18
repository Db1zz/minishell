/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_external.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:28:41 by jroseiro          #+#    #+#             */
/*   Updated: 2024/11/18 16:07:06 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

static void	execute_child(char *cmd_path, t_cmd *cmd, t_list *env)
{
	char **envp;

	envp = env_list_to_array(env);
	execve(cmd_path, cmd->args, envp);
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", 
		cmd->args[0], strerror(errno));
	free_2dmatrix(envp);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

int	execute_external(t_cmd *cmd, t_list *env)
{
	char    *cmd_path;
	pid_t   pid;
	int     status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (EXIT_FAILURE);
	cmd_path = find_cmd_path(cmd->args[0], env);
	if (!cmd_path)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", 
			cmd->args[0]);
		return (EXIT_NOT_FOUND);
	}
	pid = fork();
	if (pid < 0)
	{
		free(cmd_path);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		execute_child(cmd_path, cmd, env);
	free(cmd_path);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
