/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:18:25 by gonische          #+#    #+#             */
/*   Updated: 2024/09/28 23:47:46 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

/**
 * skip_spaces - Skips over spaces in the input string.
 * 
 * @param s: The input string.
 * 
 * This function skips over whitespace characters and returns the 
 * number of spaces skipped. - FIXME
 * 
 * @return int: The number of spaces skipped.
 */
int	skip_spaces(char const *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0); 
	while (is_space(s[i]))
		i++;
	return (i);
}

/**
 * str_to_token_type - Converts a string to its corresponding token type.
 * 
 * @param s: The string representing an operator or word.
 * 
 * This function maps specific characters or operators to token types 
 * such as T_HEREDOC, T_APPEND, T_IN, T_OUT, T_PIPE, or T_WORD.
 * 
 * @return t_token_type: The corresponding token type.
 */
t_token_type	str_to_token_type(const char *s)
{
	if (!s || !s[0])
		return (T_UNKNOWN);
	else if (s[0] == '<' && s[1] == '<')
		return (T_HEREDOC);
	else if (s[0] == '>' && s[1] == '>')
		return (T_APPEND);
	else if (s[0] == '<')
		return (T_IN);
	else if (s[0] == '>')
		return (T_OUT);
	else if (s[0] == '|')
		return (T_PIPE);
	else if (s[0] != ' ' && s[0] != '\t')
		return (T_WORD);
	else
		return (T_UNKNOWN);
}
