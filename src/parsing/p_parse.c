/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:24:24 by gonische          #+#    #+#             */
/*   Updated: 2024/09/25 13:53:04 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

char	*expand_variable(char **str, t_list *env)
{
	int		i;
	char	*key;
	char	*env_val;
	char	*val;

	i = 1;
	val = NULL;
	if ((*str)[0] != '$')
		return (NULL);
	if ((*str)[0] && ft_isdigit((*str[0])))
	{
		*str += 2;
		return (ft_substr(*str, 0, 2));
	}
	while (ft_isalpha((*str)[i]) || ft_isdigit((*str[i])) || (*str)[i] == '_')
		i++;
	if (i == 1)
		return (ft_strdup("$"));
	key = ft_substr(*str, 1, i - 1);
	env_val = get_env(env, key);
	if (env_val)
		val = ft_substr(*str, i, ft_strlen(env_val + i));
	return (*str += i, free(key), val);
}

char	*parse_word(char **input, char quote, t_list *env)
{
	char	*word;
	char	*start;

	word = "";
	start = *input;
	while (**input || !is_metachar(*input, quote) || !is_quote(**input))
		start++;
	if (is_quote(*start))
		parse_word(&start, *start, env);
	if (*start == '$' && quote != "'")
		expand_variable(&start, env);
	return (word);
}

char	*parse_operator(char **input)
{
	int		operator_len;
	char	*operator_str;

	operator_len = is_operator(*input);
	if (!operator_len)
		return (NULL);
	operator_str = ft_substr(*input, 0, operator_len);
	*input = *input + operator_len;
	return (operator_str);
}

t_token	*lexer(char **input, t_token **tokens)
{
}

t_token	*tokenizer(char *input)
{
	t_token	*tokens;

	while (input)
	{
		lexer(&tokens, &input);
	}
}
