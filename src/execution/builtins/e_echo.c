/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:17:16 by jroseiro          #+#    #+#             */
/*   Updated: 2024/10/29 12:08:37 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../e_execute.h"

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

int	builtin_echo(char **args)
{
	int		i;
	bool	newline;

	newline = true;
	i = 1;

	// check for -n flag
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		newline = false;
		i++;
	}

	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");

	return (EXIT_SUCCESS);
}
