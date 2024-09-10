/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_booleans.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:19:19 by gonische          #+#    #+#             */
/*   Updated: 2024/09/10 18:20:33 by gonische         ###   ########.fr       */
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

bool	is_operator(const char *s)
{
	return ((s[0] == '<' && (s + 1) && s[1] == '<')
			|| (s[0] == '>' && (s + 1) && s[1] == '>')
			|| (s[0] == '>')
			|| (s[0] == '<')
			|| (s[0] == '|')
			|| (s[0] == '$'));
}

bool	is_metachar(const char *s)
{
	if (!s || s[0] == '\0')
		return (false);
	return (is_space(*s) || is_operator(*s));
}

