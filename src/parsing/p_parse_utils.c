/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:18:25 by gonische          #+#    #+#             */
/*   Updated: 2024/09/20 18:37:48 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

/**
 * combine_words - Combines a list of words into a single string.
 * 
 * @param words: The list of words to combine.
 * 
 * This function iterates through a list of words, concatenates 
 * them, and returns the resulting string. It uses ft_strjoin to 
 * concatenate and handles memory allocation errors.
 * 
 * @return char*: The combined string, or NULL if the list is empty.
 */
char	*combine_words(t_list *words)
{
	char	*word;
	char	*temp;
	if (!words)
		return (NULL);
	word = ft_calloc(1, 1);
	if (!word)
		ft_printf("Calloc failed\n");
	while (words)
	{
		temp = word;
		word = ft_strjoin(word, (char *)words->content);
		words = words->next;
		if (temp)
			free(temp);
	}
	return (word);
}

/**
 * skip_spaces - Skips over spaces in the input string.
 * 
 * @param s: The input string.
 * 
 * This function skips over whitespace characters and returns the 
 * number of spaces skipped.
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
	else if (s[0] != ' ' && s[0] != '	')
		return (T_WORD);
	else
		return (T_UNKNOWN);
}
