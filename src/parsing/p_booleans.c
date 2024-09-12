/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_booleans.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:19:19 by gonische          #+#    #+#             */
/*   Updated: 2024/09/12 18:41:33 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_space(char c)
{
	return (c == ' ' || c == '	');
}

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_operator(const char *s)
{
	if (!s || !s[0])
		return (0);
	if ((s[0] == '<' && (s + 1) && s[1] == '<')
			|| (s[0] == '>' && (s + 1) && s[1] == '>'))
			return (2);
	else if ((s[0] == '>')
			|| (s[0] == '<')
			|| (s[0] == '|'))
		return (1);
	else
		return (0);
}

bool	is_metachar(const char *s, char quote)
{
	if (!s || s[0] == '\0' || is_quote(quote))
		return (false);
	return (is_space(s[0]) || is_operator(s));
}

