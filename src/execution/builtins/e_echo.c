/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:17:16 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 17:07:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_builtins.h"

/*
** check_flag - check if arg is -n
** if multiple -n, alol are skipped
** Example: echo -n -n -n hello -> prints "hello" (no newline)
*/
static int	check_flag(char **args, int *newline)
{
	int	i;
	int	j;

	i = 1;
	*newline = 0;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == 'n')
		{
			j = 2;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				*newline = 1;
				i++;
				continue ;
			}
		}
		break ;
	}
	return (i);
}

/*
** builtin_echo - Implements the echo command
** 
** @args: NULL-terminated array of arguments
**        args[0] is "echo"
**        args[1] might be "-n" (optional)
**        remaining args are the strings to print
** @env: environment list (unused in echo)
**
** echo behavior:
** - Prints its arguments separated by spaces
** - Adds newline at the end unless -n option is present
** - Returns 0 (success) always, like bash does
**
** Examples:
** echo hello world     -> prints: hello world\n
** echo -n hello world  -> prints: hello world
** echo                -> prints: \n
** echo -n             -> prints: nothing
*/
int	builtin_echo(char **args, t_shell *shell)
{
	int	i;
	int	newline;

	(void)shell;
	i = check_flag(args, &newline);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
