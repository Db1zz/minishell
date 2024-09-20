/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_mem_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:34:51 by gonische          #+#    #+#             */
/*   Updated: 2024/09/20 18:39:08 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

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
static void	free_tokens(t_token *tokens)
{
	t_token *next;

	while (tokens)
	{
		if (tokens->value)
			free(tokens->value);
		next = tokens->next;
		free(tokens);
		tokens = next;
	}
}

/**
 * free_cmd_table - Frees the memory allocated for the command table.
 * 
 * @param cmd_table: The command table to be freed.
 * 
 * This function iterates through the command table, freeing each 
 * command's redirections and arguments, and then frees the command 
 * structure itself.
 * 
 * @return void
 */
static void	free_cmd_table(t_cmd *cmd_table)
{
	t_cmd	*next;

	while (cmd_table)
	{
		free_tokens(cmd_table->redirections);
		free_2dmatrix(cmd_table->args);
		next = cmd_table;
		free(cmd_table);
		cmd_table = next;
	}
}


/**
 * clean_memory - Frees memory allocated for the command table and tokens.
 * 
 * @param cmd_table: The command table to be freed.
 * @param tokens: The list of tokens to be freed.
 * 
 * This function frees both the command table and the token list to 
 * ensure proper memory management.
 * 
 * @return void
 */
void	clean_memory(t_cmd *cmd_table, t_token *tokens)
{
	free_cmd_table(cmd_table);
	free_tokens(tokens);
}
