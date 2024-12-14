/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:20:57 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 16:40:51 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_builtins.h"

/*
** get_target_path - Get the target directory for the cd command
**
** @args: Command arguments (args[1] is the target path if provided)
** @env: Environment variables list (for resolving HOME)
**
** Returns:
** - Allocated string with the resolved target path
** - NULL if HOME is not set when needed
*/
char	*get_target_path(char **args, t_env *env)
{
	char	*path;
	t_env	*home;

	if (!args[1] || args[1][0] == '~')
	{
		home = get_env(env, "HOME");
		if (!home || !home->value)
		{
			ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
			return (NULL);
		}
		if (!args[1])
			return (ft_strdup(home->value));
		path = ft_strjoin(home->value, args[1] + 1);
	}
	path = ft_strdup(args[1]);
	return (path);
}

/*
** handle_path_error - Prints error message for invalid path or unset HOME
**
** @args: Command arguments (args[1] is the target path if provided)
**
** Returns:
** - EXIT_FAILURE (always)
**
** Notes:
** - Prints "no such file or directory" or "HOME not set" error message
**   depending on the context.
*/
int	handle_path_error(char **args)
{
	const char	*error_path;

	if (args[1])
		error_path = args[1];
	else
		error_path = "HOME";
	ft_dprintf(STDERR_FILENO, MSG_CD_ERROR,
		error_path, "no such file or directory");
	return (EXIT_FAILURE);
}

/*
** handle_minus - Resolves the OLDPWD path for "cd -" command
**
** @env: Environment variables list (to retrieve OLDPWD)
**
** Returns:
** - Allocated string with OLDPWD value if it is set
** - NULL if OLDPWD is not set
**
** Notes:
** - Prints "OLDPWD not set" if OLDPWD is missing.
** - Prints the resolved OLDPWD path to the standard output.
*/
char	*handle_minus(t_env *env)
{
	t_env	*oldpwd;

	oldpwd = get_env(env, "OLDPWD");
	if (!oldpwd || !oldpwd->value)
	{
		ft_dprintf(STDERR_FILENO, "cd: OLDPWD not set\n");
		return (NULL);
	}
	printf("%s\n", oldpwd->value);
	return (ft_strdup(oldpwd->value));
}

/*
** change_dir - Changes the current working directory
**
** @path: The target directory to change into
**
** Returns:
** - EXIT_SUCCESS if the directory is successfully changed
** - EXIT_FAILURE if an error occurs
**
** Notes:
** - Prints specific error messages for permission issues, non-existent paths,
**   or other errors based on errno.
*/
int	change_dir(const char *path)
{
	if (chdir(path) < 0)
	{
		if (errno == EACCES)
			ft_dprintf(STDERR_FILENO, MSG_CD_ERROR, path, "Permission denied");
		else if (errno == ENOENT)
			ft_dprintf(STDERR_FILENO, MSG_CD_ERROR, path,
				"No such file or directory");
		else
			ft_dprintf(STDERR_FILENO, MSG_CD_ERROR, path, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
** update_env_var - Updates or adds an environment variable
**
** @env: The environment variables list
** @key: The key of the variable to update (e.g., "PWD" or "OLDPWD")
** @value: The new value to set for the variable
**
** Returns:
** - None
**
** Notes:
** - Frees the old value if the variable already exists.
** - Adds a new variable if it does not exist in the list.
*/

void	update_env_var(t_env *env, char *key, char *value)
{
	t_env	*var;

	var = get_env(env, key);
	if (var)
	{
		if (var->value)
			free(var->value);
		var->value = ft_strdup(value);
	}
	else
		env_push_back(&env, ft_strdup(key), ft_strdup(value));
}
