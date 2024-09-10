/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:11:34 by gonische          #+#    #+#             */
/*   Updated: 2024/09/09 21:40:59 by gonische         ###   ########.fr       */
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

bool	is_space(const char	c)
{
	return (c == ' ' || c == '	');
}

int	is_metachar(const char *s)
{
	if (!s || s[0] == '\0')
		return (0);
	if (s[0] == ' ')
		return (1);
	else if (s[0] == '	')
		return (1);
	else if (s[0] == '<' && (s + 1) && s[1] == '<')
		return (2);
	else if (s[0] == '>' && (s + 1) && s[1] == '>')
		return (2);
	else if (s[0] == '>')
		return (1);
	else if (s[0] == '<')
		return (1);
	else if (s[0] == '|')
		return (1);
	else if (s[0] == '$')
		return (1);
	else
		return (0);
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
