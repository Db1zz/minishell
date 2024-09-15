/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:44:15 by gonische          #+#    #+#             */
/*   Updated: 2024/09/14 16:23:34 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	display_error(const char **msg, int errnum)
{
	char	*error;

	error = strerror(errnum);
	if (msg)
	{
		while (*msg)
			ft_printf("%s", *msg++);
	}
	if (error)
		ft_printf("%s\n", error);
}

// void	fatal_error(const char **msg, int errnum)
// {
	
// }
