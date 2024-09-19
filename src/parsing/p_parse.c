/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:40:56 by gonische          #+#    #+#             */
/*   Updated: 2024/09/19 16:57:41 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (!s[i])
	{
		ft_printf("Syntax error, unclosed quote!\n"); // TODO
		exit(-1); // TODO: just free memory and return to the shell loop
	}
	return (i + 1);
}

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

static int	parse_operator(char const *s, t_list *env, t_token **tokens)
{
	char	*token_value;
	int		op_len;
	char	*op_str;
	int		i;

	i = 0;
	token_value = NULL;
	op_len = is_operator(s);
	if (!op_len)
		return (0);
	op_str = ft_substr(s, 0, op_len);
	i += skip_spaces(s + op_len);
	i += parse_word(s + op_len + i, env, &token_value);
	if (token_value == NULL)
		ft_printf("Syntax error!\n"); // TODO
	add_token(tokens, alloc_token(str_to_token_type(op_str), token_value));
	return (free(op_str), op_len + i);
}

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
			add_token(&result, alloc_token(TOKEN_WORD, word));
	}
	return (result);
}


t_cmd	*parse_input(char *input, t_list *env)
{
	t_token		*tokens;
	t_cmd		*cmd_table;

	if (!input)
		return (NULL);
	tokens = tokenize(input, env);
	cmd_table = NULL;
	print_tokens(tokens);
	if (tokens)
		cmd_table = build_cmd_table(tokens);
	free (input);
	return (cmd_table); // TODO
}
