/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:16:38 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 01:47:31 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"
#include "env.h"
#include "minishell.h"
#include <linux/limits.h>

/*
** get_target_path - Get the target directory for cd
**
** @args: Command arguments (args[1] is the target path if provided)
** @env: Environment variables list (for HOME directory)
**
** Returns:
** - Allocated string with target path
** - NULL if HOME not set when needed
*/

static char *get_target_path(char **args, t_env *env)
{
	char	*path;
	t_env	*home;

	if (!args[1])
	{
		home = get_env(env, "HOME");
		if (!home)
			return (NULL);
		path = ft_strdup(home->value);
	}
	else
		path = ft_strdup(args[1]);
	
	return (path);
}

static int handle_path_error(char **args)
{
	const char  *error_path;

	error_path = "HOME";
	if (args[1])
		error_path = args[1];
	ft_dprintf(STDERR_FILENO, MSG_CD_ERROR, error_path, "no such variable");
	return (EXIT_FAILURE);
}

static int change_dir(const char *path)
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


static void	update_env_var(t_env *env, char *key, char *value)
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

/*
** builtin_cd - Implements the cd command
**
** @args: NULL-terminated array of arguments
**        args[0] is "cd"
**        args[1] is target path (optional)
** @env: environment list (needed for HOME)
**
** cd behavior:
** - With no args: change to HOME directory
** - With path arg: change to specified path
** - Returns 0 on success, 1 on any error
** - Prints appropriate error messages to stderr
*/

int builtin_cd(char **args, t_shell *shell)
{
	char	cwd[PATH_MAX];
	char    *path;
	int     ret;

	if (args[1] && args[2])
	{
		ft_dprintf(STDERR_FILENO, MSG_CD_USAGE);
		return (EXIT_FAILURE);
	}

	// Get target path
	path = get_target_path(args, shell->env);
	if (!path)
		return (handle_path_error(args));
	
	// Update OLDPWD bfr changing dirs
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(shell->env, "OLDPWD", cwd);
	ret = change_dir(path);
	free(path);

	// Update PWD on success
	if (ret == EXIT_SUCCESS && getcwd(cwd, sizeof(cwd)))
		update_env_var(shell->env, "PWD", cwd);
	return (ret);
}


/*
**	$ cd				# Goes to home directory
**	$ cd /tmp			# Goes to /tmp
**	$ cd ..				# Goes up one dir
**	$ cd nonexistant	# Error: No such file or dir
**	$ cd /root			# Error: permission denied
**	$ cd a b c			# Error: Too many args
*/