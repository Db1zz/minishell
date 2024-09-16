/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:33:43 by gonische          #+#    #+#             */
/*   Updated: 2024/09/16 14:48:48 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	destroy_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		if (token->value)
			free (token->value);
		temp = token;
		token = token->next;
		free(temp);
	}
}

static void	destroy_cmd_tables(t_cmd **cmd_tables)
{
	int	i;

	i = 0;
	while (cmd_tables[i])
		free (cmd_tables[i++]);
}

void	clean_memory(t_shell *shell)
{
	if (!shell)
		return ;
	destroy_tokens(shell->tokens);
	destroy_cmd_tables(shell->cmds);
}
