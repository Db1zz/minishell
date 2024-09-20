/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:40:56 by gonische          #+#    #+#             */
/*   Updated: 2024/09/20 19:01:41 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

/**
 * parse_quote - Parses a quoted section of a string and handles 
 * variable expansion if inside double quotes.
 * 
 * @param s: The string to parse, starting with a quote character.
 * @param env: List of environment variables for expansion.
 * @param words: List to store parsed words.
 * 
 * This function processes characters inside quotes, expanding 
 * variables if within double quotes. If the quote is unclosed, 
 * it prints an error and exits.
 * 
 * @return int: The number of characters processed.
 */
static int	parse_quote(char const *s, t_list *env, t_list **words)
{
	char	quote;
	int		i;
	int		j;

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
	if (!s[i])
	{
		ft_printf("Syntax error, unclosed quote!\n"); // TODO
		exit(-1); // TODO: just free memory and return to the shell loop
	}
	return (i + 1);
}

/**
 * parse_word - Parses a word from the input string, handling 
 * variable expansion and quoted sections.
 * 
 * @param s: The string to parse.
 * @param env: List of environment variables.
 * @param str_out: Pointer to store the combined parsed words.
 * 
 * This function extracts words, handling variables and quoted 
 * segments, and combines them into a single string.
 * 
 * @return int: The number of characters processed.
 */
static int	parse_word(char const *s, t_list *env, char	**str_out)
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
	{
		*str_out = combine_words(words);
		ft_lstclear(&words, free);
	}
	return (i);
}

/**
 * parse_operator - Parses an operator from the input string and 
 * creates a corresponding token.
 * 
 * @param s: The string to parse.
 * @param env: List of environment variables.
 * @param tokens: Pointer to the list of tokens to store the result.
 * 
 * This function checks if the string starts with an operator, 
 * creates a token, and parses a word if the operator is not 
 * a command separator.
 * 
 * @return int: The number of characters processed.
 */
static int	parse_operator(char const *s, t_list *env, t_token **tokens)
{
	char	*token_value;
	int		op_len;
	char	*op_str;
	int		i;
	t_token	*token;

	i = 0;
	token_value = NULL;
	op_len = is_operator(s);
	if (!op_len)
		return (0);
	op_str = ft_substr(s, 0, op_len);
	token = alloc_token(str_to_token_type(op_str), NULL);
	if (!is_cmd_spearator(token))
	{
		i += skip_spaces(s + op_len);
		i += parse_word(s + op_len + i, env, &token_value);
		if (token_value == NULL)
			ft_printf("Syntax error!\n"); // TODO
		token->value = token_value;
	}
	add_token(tokens, token);
	return (free(op_str), op_len + i);
}

/**
 * tokenize - Tokenizes the input string into a list of tokens.
 * 
 * @param s: The input string to tokenize.
 * @param env: List of environment variables.
 * 
 * This function splits the input string into tokens by parsing 
 * operators and words, handling variable expansion and spaces.
 * 
 * @return t_token*: The list of tokens generated.
 */
static t_token	*tokenize(char const *s, t_list *env)
{
	t_token	*result;
	char	*word;
	int		i;

	if (!s)
		return (NULL);
	result = NULL;
	word = NULL;
	i = 0;
	while (s[i])
	{
		i += skip_spaces(s + i);
		if (!s[i])
			continue ;
		i += parse_operator(s + i, env, &result);
		i += parse_word(s + i, env, &word);
		if (word)
		{
			add_token(&result, alloc_token(T_WORD, word));
			word = NULL;
		}
	}
	return (result);
}

/**
 * parse_input - Parses the input string into a command structure.
 * 
 * @param input: The input string to parse.
 * @param env: List of environment variables.
 * 
 * This function tokenizes the input and builds a command table. 
 * It also prints debug information such as tokens and command 
 * table contents.
 * 
 * @return t_cmd*: The generated command table.
 */
t_cmd	*parse_input(char *input, t_list *env)
{
	t_token	*tokens;
	t_cmd	*cmd_table;

	if (!input)
		return (NULL);
	tokens = tokenize(input, env);
	cmd_table = NULL;
	print_tokens(tokens);
	if (tokens)
	{
		cmd_table = build_cmd_table(tokens);
		print_cmd_table(cmd_table);
	}
	free_tokens(tokens);
	free(input);
	return (cmd_table); // TODO
}
