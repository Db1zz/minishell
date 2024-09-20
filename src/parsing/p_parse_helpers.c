/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:19:19 by gonische          #+#    #+#             */
/*   Updated: 2024/09/20 18:38:35 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

/**
 * is_space - Checks if a character is a space or tab.
 * 
 * @param c: The character to check.
 * 
 * This function checks if the character is a space (' ') or 
 * a tab ('\t').
 * 
 * @return bool: True if the character is a space, false otherwise.
 */
bool	is_space(char c)
{
	return (c == ' ' || c == '	');
}


/**
 * is_quote - Checks if a character is a quote.
 * 
 * @param c: The character to check.
 * 
 * This function checks if the character is a single quote ('\'') 
 * or a double quote ('"').
 * 
 * @return bool: True if the character is a quote, false otherwise.
 */
bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}


/**
 * is_operator - Checks if the string starts with an operator.
 * 
 * @param s: The input string.
 * 
 * This function checks if the string begins with one of the 
 * operators ('<', '>', '|'). It returns the length of the 
 * operator (1 or 2 characters).
 * 
 * @return int: The length of the operator or 0 if none found.
 */
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

/**
 * is_metachar - Checks if the string starts with a metacharacter.
 * 
 * @param s: The input string.
 * 
 * This function checks if the string begins with a space, operator, 
 * or if it is empty. Metacharacters include spaces and operators.
 * 
 * @return bool: True if the string starts with a metacharacter.
 */
bool	is_metachar(const char *s)
{
	if (!s || s[0] == '\0')
		return (false);
	return (is_space(s[0]) || is_operator(s));
}

/**
 * is_word - Checks if the string starts with a word.
 * 
 * @param s: The input string.
 * 
 * This function checks if the string begins with a word, meaning 
 * it is not a metacharacter, variable ('$'), or quote.
 * 
 * @return bool: True if the string starts with a word.
 */
bool	is_word(const char *s)
{
	if (!s || !s[0])
		return (false);
	return (!is_metachar(s) && s[0] != '$' && !is_quote(s[0]));
}
