/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:16:38 by jroseiro          #+#    #+#             */
/*   Updated: 2024/11/28 15:46:07 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"
#include "minishell.h"

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

static char *get_target_path(char **args, t_list *env)
{
	char    *path;
	char    *home;

	if (!args[1])
	{
		home = get_env(env, "HOME");
		if (!home)
			return (NULL);
		path = ft_strdup(ft_strchr(home, '=') + 1);
	}
	else
		path = ft_strdup(args[1]);
	
	return (path);
}

// static int path_error(char **args) // path error handling
// {
// 	const char	*error_path;

// 	error_path = "HOME";
// 	if (args[1])
// 		error_path = args[1];
// 	ft_dprintf(STDERR_FILENO, MSG_CD_ERROR, error_path, "no such variable");
// 	return (EXIT_FAILURE);
// }

// static int	chdir_error(const char *path) // changing dir error handling
// {
// 	if (errno == EACCES)
// 		ft_dprintf(STDERR_FILENO, MSG_CD_ERROR, path, "Permission denied");
// 	else if (errno == ENOENT)
// 		ft_dprintf(STDERR_FILENO, MSG_CD_ERROR, path, 
//             "No such file or directory");
// 	else
// 		ft_dprintf(STDERR_FILENO, MSG_CD_ERROR, path, strerror(errno));
// 	return (EXIT_FAILURE);
// }

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

int builtin_cd(char **args, t_list *env)
{
	char    *path;
	int     ret;

	if (args[1] && args[2])
	{
		ft_dprintf(STDERR_FILENO, MSG_CD_USAGE);
		return (EXIT_FAILURE);
	}

	path = get_target_path(args, env);
	if (!path)
		return (handle_path_error(args));

	ret = change_dir(path);
	free(path);
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