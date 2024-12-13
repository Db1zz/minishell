/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_path.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:45:25 by zrz               #+#    #+#             */
/*   Updated: 2024/12/12 17:40:44 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"
#include "minishell.h"

static char	*check_direct_path(char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		return (NULL);
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

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	while (paths[i] && !full_path)
	{
		full_path = try_path_dir(paths[i], cmd);
		i++;
	}
	free_2dmatrix(paths);
	return (full_path);
}

char	*find_cmd_path(char *cmd, t_list *env)
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
	return (search_in_paths(paths, cmd));
}
