/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:19:38 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 17:08:03 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_builtins.h"

/*
** is_numeric - Checks if string is a valid number
** Allows for one optional leading + or -
*/
static int	is_num(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** get_exit_code - Convert string to exit code (0-255)
** Returns -1 if number is invalid
*/

static int	get_exit_code(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		num = (num * 10) + (str[i] - '0');
		if (num > INT_MAX)
			return (-1);
		i++;
	}
	num *= sign;
	return ((num % 256 + 256) % 256);
}

/*
** builtin_exit - Implements the exit command
** Usage: exit [n]
** n is optional exit code (0-255)
** Without n, uses last command's exit status
*/
int	builtin_exit(char **args, t_shell *shell)
{
	int	exit_code;

	(void)shell;
	if (!args[1])
		(destroy_shell(shell), exit(EXIT_SUCCESS));
	if (!is_num(args[1]))
	{
		ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			args[1]);
		return (EXIT_MISUSE);
	}
	if (args[2])
	{
		ft_dprintf(STDERR_FILENO, "exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	exit_code = get_exit_code(args[1]);
	(destroy_shell(shell), exit(exit_code));
}
