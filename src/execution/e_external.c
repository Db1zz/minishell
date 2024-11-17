/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_external.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:28:41 by jroseiro          #+#    #+#             */
/*   Updated: 2024/11/17 18:03:51 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

static char	*check_direct_path(char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		return (NULL);
	// If command contains '/' treat as direct path
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*try_path_dir(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(full_path, X_OK) != 0)
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static char	*find_in_path_dirs(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = try_path_dir(paths[i], cmd);
		if (full_path)
		{
			free_2dmatrix(paths);
			return (full_path);
		}
		i++;
	}
	free_2dmatrix(paths);
	return (NULL);
}

static char	*find_cmd_path(char *cmd, t_list *env)
{
	char	**paths;
	char	*path_var;
	char	*direct_path;

	if (!cmd || !cmd[0])
		return (NULL);
	direct_path = check_direct_path(cmd);
	if (direct_path)
		return (direct_path);
	path_var = get_env(env, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(ft_strchr(path_var, '=') + 1, ':');
	if (!paths)
		return (NULL);
	return (find_in_path_dirs(paths, cmd));
}

static int	execute_cmd_fork(char *cmd_path, t_cmd *cmd, t_list *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		free(cmd_path);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		handle_child_process(cmd_path, cmd, env);

	free(cmd_path);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_external(t_cmd *cmd, t_list *env)
{
	char	*cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (EXIT_FAILURE);
	cmd_path = find_cmd_path(cmd->args[0], env);
	if (!cmd_path)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", 
			cmd->args[0]);
		return (EXIT_NOT_FOUND);
	}
	return (execute_cmdd_fork(cmd_path, cmd, env));
}


int execute_external(t_cmd *cmd, t_list *env)
{
    char    *cmd_path;
    pid_t   pid;
    int     status;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (EXIT_FAILURE);
    cmd_path = find_command_path(cmd->args[0], env);
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
