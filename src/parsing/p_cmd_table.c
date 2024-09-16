/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:03:20 by gonische          #+#    #+#             */
/*   Updated: 2024/09/16 17:37:32 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	alloc_cmd_table(t_shell *d)
{
	t_cmd	**cmd_table;
	size_t	cmd_table_size;
	t_token	*head;

	cmd_table_size = 0;
	head = d->tokens;
	while (head)
	{
		
	}
	/*
		Count amount of commands
		Allocate table;
		Set pointer for d->cmds to cmd_table;
	*/
}
