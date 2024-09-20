/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:03:20 by gonische          #+#    #+#             */
/*   Updated: 2024/09/20 18:40:22 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

/**
 * get_redirections - Extracts redirection tokens from the token list.
 * 
 * @param tokens: The list of tokens to scan for redirections.
 * 
 * This function goes through the token list and duplicates any 
 * redirection tokens, adding them to a separate redirection list.
 * 
 * @return t_token*: The list of redirection tokens.
 */
static t_token *get_redirections(t_token *tokens)
{
	t_token	*redirections;

	redirections = NULL;
	while (tokens && !is_cmd_spearator(tokens))
	{
		if (is_redirection(tokens))
			add_token(&redirections, dup_token(tokens));
		tokens = tokens->next;
	}
	return (redirections);
}

/**
 * count_args - Counts the number of argument tokens.
 * 
 * @param tokens: The list of tokens to scan for arguments.
 * 
 * This function counts the number of non-redirection tokens, 
 * which are treated as arguments.
 * 
 * @return size_t: The number of argument tokens.
 */
static size_t	count_args(t_token *tokens)
{
	size_t	result;

	result = 0;
	while (tokens && !is_cmd_spearator(tokens))
	{
		if (!is_redirection(tokens))
			result++;
		tokens = tokens->next;
	}
	return (result);
}

/**
 * get_args - Retrieves the argument tokens and creates an array of strings.
 * 
 * @param tokens: The list of tokens to scan for arguments.
 * 
 * This function allocates memory for an array of argument strings and 
 * populates it by copying the argument tokens.
 * 
 * @return char**: An array of argument strings, or NULL if no arguments.
 */
static char	**get_args(t_token *tokens)
{
	char	**args;
	size_t	args_size;
	size_t	i;

	i = 0;
	args_size = count_args(tokens);
	if (args_size == 0)
		return (NULL); // TODO: Display error and stop execution.
	args = ft_calloc(args_size + 1, sizeof(char *));
	while (i != args_size)
	{
		if (!is_redirection(tokens) && tokens->value)
			args[i++] = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	return (args);
}

/**
 * get_next_cmd_tokens - Finds the next command separator in the token list.
 * 
 * @param tokens: The list of tokens to scan.
 * 
 * This function advances the token pointer to the next command separator, 
 * returning the tokens after the separator.
 * 
 * @return t_token*: The remaining tokens after the separator.
 */
static t_token	*get_next_cmd_tokens(t_token *tokens)
{
	if (!tokens)
		return (NULL); // TODO
	while (tokens && !is_cmd_spearator(tokens))
		tokens = tokens->next;
	if (is_cmd_spearator(tokens))
		tokens = tokens->next;
	return (tokens);
}

/**
 * build_cmd_table - Builds a command table from a token list.
 * 
 * @param tokens: The list of tokens to parse into a command table.
 * 
 * This function processes a list of tokens, extracting arguments 
 * and redirections, and organizes them into a command table structure.
 * 
 * @return t_cmd*: A linked list representing the command table.
 */
t_cmd	*build_cmd_table(t_token *tokens)
{
	t_cmd	*cmd_table;
	t_cmd	*last_cmd;
	t_cmd	*cmd;
	t_token	*curr_tokens;

	if (!tokens)
		return (NULL);
	curr_tokens = tokens;
	cmd_table = NULL;
	while (curr_tokens)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		cmd->args = get_args(curr_tokens);
		cmd->redirections = get_redirections(curr_tokens);
		if (!cmd_table)
			cmd_table = cmd;
		else
			last_cmd->next = cmd;
		last_cmd = cmd;
		curr_tokens = get_next_cmd_tokens(curr_tokens);
	}
	return (cmd_table);
}

// =========================== DEBUG ONLY =========================== //

/**
 * print_cmd_table - Debug function to print the command table.
 * 
 * @param cmd_table: The command table to print.
 * 
 * This function prints the arguments and redirections for each 
 * command in the command table.
 * 
 * @return void
 */
void	print_cmd_table(t_cmd *cmd_table)
{
	int		i;
	t_token	*redirections;

	while (cmd_table)
	{
		i = 0;
		redirections = cmd_table->redirections;
		ft_printf("Args: ");
		while (cmd_table->args && cmd_table->args[i])
			ft_printf("[%s]", cmd_table->args[i++]);
		ft_printf("\nRedirections: ");
		while (redirections)
		{
			ft_printf("[%s]", redirections->value);
			redirections = redirections->next;
		}
		ft_printf("\n");
		cmd_table = cmd_table->next;
	}
}
