/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_table_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:23:02 by gonische          #+#    #+#             */
/*   Updated: 2024/09/19 16:32:37 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_cmd_spearator(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == TOKEN_PIPE
			|| token->type == TOKEN_AND
			|| token->type == TOKEN_OR);	
}

bool	is_redirection(t_token *token)
{
	if (!token)
		return (false);
	return ((token->type == TOKEN_IN)
			|| (token->type == TOKEN_OUT)
			|| (token->type == TOKEN_INDELIMITER)
			|| (token->type == TOKEN_OUTAPPEND));
}

t_token	*dup_token(t_token *token)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(token));
	new_token->next = NULL;
	if (token->value)
		new_token->value = ft_strdup(token->value);
	else
		new_token->value = NULL;
	new_token->type = token->type;
	return (new_token);
}
