/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_list_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:54:18 by gonische          #+#    #+#             */
/*   Updated: 2024/09/27 23:46:14 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

/**
 * is_redirection - Checks if the given token is a redirection token.
 * 
 * @param token: The token to check.
 * 
 * The function returns true if the token type indicates 
 * a redirection (e.g., T_IN, T_OUT, T_HEREDOC, T_APPEND).
 * 
 * @return bool: true if redirection, false otherwise.
 */
bool	is_redirection(t_token *token)
{
	if (!token)
		return (false);
	return ((token->type == T_IN)
			|| (token->type == T_OUT)
			|| (token->type == T_HEREDOC)
			|| (token->type == T_APPEND));
}

/**
 * is_cmd_separator - Checks if the token is a command separator.
 * 
 * @param token: The token to check.
 * 
 * The function returns true if the token type represents a 
 * command separator like T_PIPE, T_AND, or T_OR.
 * 
 * @return bool: true if separator, false otherwise.
 */
bool	is_cmd_spearator(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == T_PIPE
			|| token->type == T_AND
			|| token->type == T_OR);
}
