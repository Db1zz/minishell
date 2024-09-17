/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:33:43 by gonische          #+#    #+#             */
/*   Updated: 2024/09/17 16:31:21 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	destroy_cmd_tables(t_cmd *cmd_tables)
{
	int		i;
	t_cmd	*temp;
	t_token	*curr_token;

	while (cmd_tables)
	{
		i = 0;
		while (cmd_tables->args && cmd_tables->args[i])
		{
			if (cmd_tables->args[i])
				free(cmd_tables->args[i]);
			i++;
		}
		if (cmd_tables->args)
			free(cmd_tables);
		curr_token = cmd_tables->redirections;
		while (curr_token)
		{
			if (curr_token->value)
				free(curr_token->value);
			curr_token = curr_token->next;
		}
		temp = cmd_tables;
		cmd_tables = cmd_tables->next;
		if (temp)
			free(temp);
	}
}
