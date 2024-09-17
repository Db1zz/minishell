/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:03:20 by gonische          #+#    #+#             */
/*   Updated: 2024/09/17 16:51:59 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_cmd_spearator(char *s)
{
	if (!s || !s[0])
		return (false);
	return ((s[1] && s[0] == '|' && s[1] == '|') ||
			(s[1] && s[0] == '&' && s[1] == '&') ||
			(s[0] == '|'));
}

static bool	is_redirection(int	token)
{
	return ((token == TOKEN_IN)
			|| (token == TOKEN_OUT)
			|| (token == TOKEN_INDELIMITER)
			|| (token == TOKEN_OUTAPPEND));
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
}

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
	while (head)
	{
		tail = head;
		head = head->next;
		tail->next = NULL;
		while (!is_cmd_spearator(tail->value))
		{
			if (tail->token == TOKEN_WORD)
				put_arg(curr_cmd, tail);
			else
				put_redirection(curr_cmd, tail);
			head = head->next;
		}
		curr_cmd->next = ft_calloc(1, sizeof(t_cmd));
		curr_cmd = curr_cmd->next;
	}
	return (cmd_table);
}
