/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:19:38 by jroseiro          #+#    #+#             */
/*   Updated: 2024/10/30 12:43:05 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../e_execute.h"

/*
** is_numeric - Checks if string is a valid number
** Allows for one optional leading + or -
*/

static int is_num(const char *str)
{
	int i;

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




/*
** builtin_exit - Implements the exit command
** Usage: exit [n]
** n is optional exit code (0-255)
** Without n, uses last command's exit status
*/

