/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:03:20 by gonische          #+#    #+#             */
/*   Updated: 2024/09/18 17:38:50 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: rewrite this shit

static bool	is_cmd_spearator(char *s)
{
	if (!s || !s[0])
		return (false);
	return ((s[1] && s[0] == '|' && s[1] == '|') ||
			(s[1] && s[0] == '&' && s[1] == '&') ||
			(s[0] == '|'));
}

static size_t	count_args(t_token *tokens)
{
	size_t	result;

	result = 0;
	while (tokens && !is_cmd_spearator(tokens->value))
	{
		if (!is_redirection(tokens->type))
			result++;
		tokens = tokens->next;
	}
	return (result);
}

static void	put_redirection(t_cmd *cmd, t_token *new)
{
	t_token	*last_redirection;

	last_redirection = cmd->redirections;
	while (last_redirection && last_redirection->next)
		last_redirection = last_redirection->next;
	if (!last_redirection)
		last_redirection = new;
	else
		last_redirection->next = new;
}

static void	put_arg(t_cmd *cmd, t_token *word)
{
	char	*arg;
	int		i;

	arg = word->value;
	free(word);
	i = 0;
	while (cmd->args[i])
		i++;
	cmd->args[i] = arg;
	free(word);
}

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

// TODO: rewrite this ugly buggy bullshit ;)
t_cmd	*build_cmd_table(t_token *tokens)
{
	t_token	*head;
	t_token	*tail;
	t_cmd	*curr_cmd;
	t_cmd	*cmd_table;

	if (!tokens)
		return (NULL);
	head = tokens;
	cmd_table = ft_calloc(1, sizeof(t_cmd));
	curr_cmd = cmd_table;
	while (tail)
	{	
		if (!is_cmd_spearator(tail->value))
		curr_cmd->args = ft_calloc(count_args(tokens), sizeof(char *));
		while (!is_cmd_spearator(tail->value) && tail)
		{
			tail = head;
			if (head)
				head = head->next;
			tail->next = NULL;
			if (tail->type == TOKEN_WORD)
				put_arg(curr_cmd, tail);
			else
				put_redirection(curr_cmd, tail);
		}
		head = head->next;
		curr_cmd->next = ft_calloc(1, sizeof(t_cmd));
		curr_cmd = curr_cmd->next;
	}
	return (cmd_table);
}
