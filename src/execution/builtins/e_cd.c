/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:16:38 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 16:29:30 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
# include <limits.h>
#elif __linux__
# include <linux/limits.h>
#endif

#include "e_builtins.h"
#include "e_execute.h"
#include "env.h"
#include "minishell.h"

/*
** validate_cd_args - Validates the number of arguments for the cd command
**
** @args: Command arguments (args[0] is "cd", args[1] is the target path)
**
** Returns:
** - 1 if arguments are valid
** - 0 if too many arguments are passed
**
** Notes:
** - Prints usage error if too many arguments are provided.
*/
static int	validate_cd_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_dprintf(STDERR_FILENO, MSG_CD_USAGE);
		return (0);
	}
	return (1);
}

/*
** resolve_cd_path - Resolves the target directory for the cd command
**
** @args: Command arguments (args[1] is the target path, optional)
** @env: Environment variables list (for HOME and OLDPWD resolution)
**
** Returns:
** - Allocated string with the resolved target directory
** - NULL if the path could not be resolved
*/
char	*resolve_cd_path(char **args, t_env *env)
{
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		return (handle_minus(env));
	return (get_target_path(args, env));
}

/*
** perform_cd - Performs the directory change and updates environment variables
**
** @path: Target directory to change to
** @env: Environment variables list (for updating PWD and OLDPWD)
** @cwd: Buffer for storing the current working directory
**
** Returns:
** - 1 if directory change was successful
** - 0 if an error occurred
**
** Notes:
** - Updates PWD and OLDPWD environment variables on success.
*/
int	perform_cd(char *path, t_env *env, char cwd[PATH_MAX])
{
	if (!getcwd(cwd, PATH_MAX))
		return (0);
	if (change_dir(path) != EXIT_SUCCESS)
		return (0);
	update_env_var(env, "OLDPWD", cwd);
	if (getcwd(cwd, PATH_MAX))
		update_env_var(env, "PWD", cwd);
	return (1);
}

/*
** builtin_cd - Implements the cd command
**
** @args: Command arguments (args[0] is "cd", args[1] is the target path)
** @shell: Shell structure containing environment variables
**
** Returns:
** - EXIT_SUCCESS on successful directory change
** - EXIT_FAILURE on any error
*/
int	builtin_cd(char **args, t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*path;
	int		ret;

	ret = EXIT_FAILURE;
	if (!validate_cd_args(args))
		return (EXIT_FAILURE);
	path = resolve_cd_path(args, shell->env);
	if (!path)
		return (handle_path_error(args));
	if (perform_cd(path, shell->env, cwd))
		ret = EXIT_SUCCESS;
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