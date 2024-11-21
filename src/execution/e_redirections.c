/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:45:40 by zrz               #+#    #+#             */
/*   Updated: 2024/11/21 19:33:47 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

static int input_redirection(char *file)
{
	
}

/*
** The general format for redirecting input is: [n]<word
**
** The general format for redirecting output is: [n]>[|]word
**
*/
static int	output_redirection(char *file, int append)
{
	
}

int	setup_redirections(t_token *redirections)
{
	t_token *curr;
	int		status;

	curr = redirections;
	while (curr)
	{
		
	}
	return (EXIT_SUCCESS);
}