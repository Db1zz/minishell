/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:19:34 by jroseiro          #+#    #+#             */
/*   Updated: 2024/10/28 19:39:49 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../e_execute.h"

/*
** builtin_pwd - Implements the pwd command (print working directory)
** @args: NULL-terminated array of arguments
**        args[0] is "pwd"
**        No options are supported
** @env: environment list (unused in pwd)
**
** pwd behavior:
** - Prints current working directory
** - Uses getcwd() to get the actual path
** - Returns 0 on success, 1 on failure
** - Prints error message to stderr on failure
**
** Examples:
** pwd         -> prints: /current/path
** pwd foo bar -> prints: /current/path (ignores extra args)
*/

int	builtin_pwd(char **args, t_list *env)
{
	char	*pwd;

	(void)args;	// PWD ignores any arguments
	(void)env;	// PWD doesn't use the environment

	// Getting the current working directory - getcwd
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_dprintf(STDERR_FILENO, MSG_PWD_ERROR, strerror(errno));
		return (EXIT_FAILURE);
	}

	// print path and clean shit up
	printf("%s\n", pwd);
	free(pwd);

	return (EXIT_SUCCESS);
}
