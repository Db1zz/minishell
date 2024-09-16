/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenizer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:18:25 by gonische          #+#    #+#             */
/*   Updated: 2024/09/16 17:16:30 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*alloc_token_from_string(char *s)
{
	t_token	*result;

	if (!s)
		return (NULL);
	result = ft_calloc(1, sizeof(t_token));
	result->token = str_to_token_type(s);
	result->value = s;
	result->next = NULL;
	return (result);
}

void	add_token(t_token **list, t_token *token)
{
	t_token	*head;

	if (!token)
		return ;
	if (!list || !*list)
		*list = token;
	else
	{
		head = *list;
		while (head->next)
			head = head->next;
		head->next = token;
	}
}

t_token	*combine_tokenize_words(t_list *words)
{
	char	*word;
	char	*temp;
	t_token	*token;

	if (!words)
		return (NULL);
	word = ft_calloc(1, 1);
	while (words)
	{
		temp = word;
		word = ft_strjoin(word, (char *)words->content);
		words = words->next;
		if (temp)
			free(temp);
	}
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
	if (s[1] && ft_isdigit(s[1]))
		return (2);
	i = 1;
	while (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_')
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
	else if (s[0] != ' ' && s[0] != '	')
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
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("%s\n", tokens->value);
		tokens = tokens->next;
	}
}
