/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:25:55 by gonische          #+#    #+#             */
/*   Updated: 2024/09/16 14:49:32 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * parse_quote - Parses a quoted string and processes its contents.
 * 
 * @param s: The string that starts with a quote (single or double).
 * @param envp: The environment variables for expanding any variables inside double quotes.
 * @param words: A list of word tokens to which parsed words will be appended.
 * 
 * This function starts by checking if the first character of `s` is a valid quote.
 * It then iterates through the string to capture the contents inside the quote, handling
 * variable expansion if it's a double quote. The parsed substrings are added to the `words` list.
 * 
 * @return i + 1: The number of characters processed, including the closing quote, or 0 if the input is invalid.
 */
static int	parse_quote(char const *s, t_list *env, t_list **words)
{
	char		quote;
	int			i;
	int			j;

	if (!s || !is_quote(s[0]))
		return (0);
	quote = s[0];
	i = 1;
	while (s[i] && s[i] != quote)
	{
		j = i;
		while (s[i] && s[i] != quote && !(quote == '"' && s[i] == '$')) 
			i++;
		if (i > j)
			ft_lstadd_back(words, ft_lstnew(ft_substr(s + j, 0, i - j)));
		if (quote == '"' && s[i] == '$')
			i += expand_variable(s + i, env, words);
	}
	return (i + 1);
}

/**
 * parse_word - Parses a non-metacharacter, non-operator word from the input string.
 * 
 * @param s: The string to parse, starting at the word.
 * @param envp: The environment variables for expanding variables when `$` is encountered.
 * @param tokens: A list of tokens to which parsed words or variable expansions will be appended.
 * 
 * This function processes a string until a metacharacter or operator is found, identifying and 
 * expanding variables or quotes if needed. The resulting tokens are combined into one word and 
 * added to the `tokens` list.
 * 
 * @return i: The number of characters processed in the word.
 */
static int	parse_word(char const *s, t_list *env, t_token **tokens)
{
	t_list	*words;
	int		i;
	int		j;

	if (!s || !*s)
		return (0);
	i = 0;
	words = NULL;
	while (s[i] && !is_metachar(s + i))
	{
		while (s[i] == '$')
			i += expand_variable(s + i, env, &words);
		while (is_quote(s[i]))
			i += parse_quote(s + i, env, &words);
		j = i;
		while (is_word(s + i))
			i++;
		if (i > j)
			ft_lstadd_back(&words, ft_lstnew(ft_substr(s + j, 0, i - j)));
	}
	if (words)
		add_token(tokens, combine_tokenize_words(words));
	return (i);
}

/**
 * parse_operator - Parses an operator (such as `<`, `>>`, etc.) from the input string.
 * 
 * @param s: The string that may start with an operator.
 * @param tokens: A list of tokens to which the operator token will be appended.
 * 
 * This function checks if the start of the string is a recognized operator and appends it to 
 * the `tokens` list. It uses `is_operator` to determine the length of the operator.
 * 
 * @return operator_len: The length of the operator parsed, or 0 if no operator is found.
 */
static int	parse_operator(char const *s, t_token **tokens)
{
	int		operator_len;
	char	*operator_str;

	operator_len = is_operator(s);
	if (!operator_len)
		return (0);
	operator_str = ft_substr(s, 0, operator_len);
	add_token(tokens, alloc_token_from_string(operator_str));
	return (operator_len);
}

/**
 * parse_tokens - Tokenizes the input string by identifying and processing operators, words, and spaces.
 * 
 * @param s: The string to be tokenized.
 * @param envp: The environment variables for expanding variables within words.
 * 
 * This function iterates through the input string, identifying spaces, operators, and words. It
 * delegates the parsing of operators to `parse_operator` and words to `parse_word`. Each parsed
 * token is appended to a result list.
 * 
 * @return result: A list of tokens parsed from the string.
 */
static t_token	*parse_tokens(char const *s, t_list *env)
{
	t_token		*result;
	int			i;

	result = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			i += parse_operator(s + i, &result);
			i += parse_word(s + i, env, &result);
		}
	}
	return (result);
}

/**
 * tokenize - Converts a string into a list of tokens (words and operators).
 * 
 * @param s: The string to tokenize.
 * @param envp: The environment variables for handling variable expansions.
 * 
 * This is the main function that takes an input string and processes it to create a list of tokens.
 * It uses the `parse_tokens` function to do the actual parsing work and handles any null input.
 * 
 * @return result: A list of tokens representing the parsed input, or NULL if the input is invalid.
 */
t_token	*tokenize(char *s, t_list *env)
{
	t_token	*result;

	if (!s)
		return (NULL);
	result = parse_tokens(s, env);
	return (result);
}
