/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenizer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:18:25 by gonische          #+#    #+#             */
/*   Updated: 2024/09/14 16:39:17 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * alloc_token - Allocates a new token and adds it to a list.
 * 
 * @param s: The string from which the token will be created.
 * @param len: The length of the token in the string.
 * 
 * This function creates a new token from the input string `s`, up to the length `len`.
 * It allocates memory for the token, determines the token type using `str_to_token_type()`,
 * and stores the corresponding substring in `t->value`. The token is then added to a new list node.
 * 
 * @return result: A pointer to the newly allocated list node containing the token, or NULL if input is invalid.
 */
t_list	*alloc_token(char const *s, size_t len)
{
	t_token	*t;
	t_list	*result;

	if (!s || !s[0])
		return (NULL);
	t = ft_calloc(1, sizeof(t_token));
	result = ft_lstnew(t);
	t->token = str_to_token_type(s);
	t->value = ft_substr(s, 0, len);
	return (result);
}

/**
 * combine_words - Combines a list of word tokens into a single token.
 * 
 * @param words: A linked list of words to combine.
 * 
 * This function iterates over a list of words, concatenating them into a single string.
 * It then allocates a new `t_token` structure, storing the concatenated string in `token->value`
 * and setting the token type to `TOKEN_WORD`.
 * 
 * @return token: A pointer to the newly allocated token containing the combined words, or NULL if input is invalid.
 */
t_token	*combine_words(t_list *words)
{
	char	*word;
	t_token	*token;

	if (!words)
		return (NULL);
	word = "";
	while (words)
	{
		word = ft_strjoin(word, (char *)words->content);
		words = words->next;
	}
	alloc_token(word, sizeof(word));
	token = ft_calloc(1, sizeof(t_token));
	token->value = word;
	token->token = TOKEN_WORD;
	return (token);
}

/**
 * expand_variable - Expands a variable from the string using the environment variables.
 * 
 * @param s: The string containing the variable, starting with a '$' character.
 * @param envp: An array of environment variables for variable expansion.
 * @param words: A list to which the expanded variable's value will be added.
 * 
 * This function parses a variable name from the string `s` after the `$` symbol and
 * searches for its value in the `envp` array. If a match is found, the value is appended
 * to the `words` list. The function handles both variable expansion and partial parsing
 * of the input string.
 * 
 * @return i: The number of characters processed in the input string.
 */
int	expand_variable(char const *s, t_list *env, t_list **words)
{
	int		i;
	char	*key;
	char	*val;
	char	*env_val;

	if (!s || s[0] != '$')
		return (0);
	i = 1;
	while (s[i] && !is_metachar(s + i) && !is_quote(s[i]) && s[i] != '$')
		i++;
	if (i == 1)
		return (ft_lstadd_back(words, ft_lstnew(ft_substr("$", 0, 1))), 1);
	key = ft_substr(s, 1, i - 1);
	env_val = get_env(env, key);
	if (env_val)
	{
		val = ft_substr(env_val, i, ft_strlen(env_val + i));
		if (val)
			ft_lstadd_back(words, ft_lstnew(val));
	}
	return (free(key), i);
}

/**
 * str_to_token_type - Determines the type of token based on the input string.
 * 
 * @param s: The string from which the token type will be inferred.
 * 
 * This function examines the input string to determine what kind of token it represents,
 * such as an input redirection (`<`), output redirection (`>`), pipe (`|`), or variable (`$`).
 * It can also recognize compound operators like `<<` or `>>`. If no match is found, it
 * defaults to returning `TOKEN_UNKNOWN`.
 * 
 * @return int: The token type (e.g., `TOKEN_IN`, `TOKEN_OUT`, `TOKEN_PIPE`), or `TOKEN_UNKNOWN` if unrecognized.
 */
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
	else if (s[0] != ' ' && s[0] != '\t')
		return (TOKEN_WORD);
	else
		return (TOKEN_UNKNOWN);
}

/**
 * print_tokens - Prints the value of each token in a linked list.
 * 
 * @param lst: A linked list of tokens to print.
 * 
 * This function iterates through a list of tokens, printing the `value` field of
 * each `t_token` structure. The function uses `ft_printf` to output the token values.
 * 
 */
void	print_tokens(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", ((t_token *)lst->content)->value);
		lst = lst->next;
	}
}
