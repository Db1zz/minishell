/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:03:20 by gonische          #+#    #+#             */
/*   Updated: 2024/09/19 17:00:17 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static char	**get_args(t_token *tokens)
{
	char	**args;
	size_t	args_size;
	size_t	i;

	i = 0;
	args_size = count_args(tokens);
	if (args_size == 0)
		return (NULL);	// TODO: Display error and stop execution.
	args = ft_calloc(args_size, sizeof(char *));
	while (i < args_size)
	{
		if (tokens->value)
			args[i] = ft_strdup(tokens->value);
		else
			args[i] = ft_strdup("get_args error");
		i++;
		tokens = tokens->next;
	}
	return (args);
}

static	t_token	*get_next_cmd_tokens(t_token *tokens)
{
	if (!tokens)
		return (NULL); // TODO
	while (tokens && !is_cmd_spearator(tokens))
		tokens = tokens->next;
	if (is_cmd_spearator(tokens))
		tokens = tokens->next;
	return (tokens);
}

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
