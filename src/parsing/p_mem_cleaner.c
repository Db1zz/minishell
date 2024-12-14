/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_mem_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:34:51 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 13:59:24 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

void	free_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*next;
	t_cmd	*current;

	if (!cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		free_tokens(current->redirections);
		free_2dmatrix(current->args);
		next = current->next;
		free(current);
		current = next;
	}
	*cmd_list = NULL;
}

/**
 * free_tokens - Frees the memory allocated for a list of tokens.
 * 
 * @param tokens: The list of tokens to be freed.
 * 
 * This function iterates through the token list, freeing each 
 * token's value and the token itself.
 * 
 * @return void
 */
void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		if (tokens->value)
			free(tokens->value);
		next = tokens->next;
		free(tokens);
		tokens = next;
	}
}
