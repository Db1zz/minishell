/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:11:34 by gonische          #+#    #+#             */
/*   Updated: 2024/09/10 18:24:49 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tokens(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", ((t_token *)lst->content)->value);
		lst = lst->next;
	}
}

int	str_to_token_type(const char *s)
{
	if (!s || !s[0])
		return (TOKEN_UNKNOWN);
	if (s[0] == '<')
		return (TOKEN_IN);
	else if (s[0] == '>')
		return (TOKEN_OUT);
	else if (s[0] == '|')
		return (TOKEN_PIPE);
	else if (s[0] == '$')
		return (TOKEN_VARIABLE);
	else if (s[0] == '<' && s[1] == '<')
		return (TOKEN_INDELIMITER);
	else if (s[0] == '>' && s[1] == '>')
		return (TOKEN_OUTAPPEND);
	else if (s[0] != ' ' && s[0] != '	')
		return (TOKEN_WORD);
	else
		return (TOKEN_UNKNOWN);
}
