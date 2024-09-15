/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:20:56 by gonische          #+#    #+#             */
/*   Updated: 2024/09/15 17:57:47 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	validate_redirections(t_list	*tokens)
{
	while (tokens)
	{
		if (((t_token *)tokens->content)->value == TOKEN_IN)
		tokens = tokens->next;
	}
}

bool	validate_tokens(t_list	*tokens)
{
	if (!tokens || !(t_token *)tokens->content)
		return (false);
	while (*tokens)
	{
		
	}
}
