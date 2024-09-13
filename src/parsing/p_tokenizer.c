/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:25:55 by gonische          #+#    #+#             */
/*   Updated: 2024/09/13 16:09:09 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list	*alloc_token(char const *s, size_t len)
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

int	expand_variable(char const *s, char const **envp, t_list **words)
{
	int		i;
	char	*key;
	char	*val;

	if (!s || s[0] != '$')
		return (0);
	i = 1;
	while (s[i] && !is_metachar(s + i) && !is_quote(s[i]))
		i++;
	key = ft_substr(s, 1, i);
	val = NULL;
	while (*envp)
	{
		if (ft_strncmp(key, *envp, i - 1) == 0)
		{
			val = ft_substr(*envp, i, ft_strlen((*envp) + i));
			if (val)
				ft_lstadd_back(words, ft_lstnew(val));
			break ;
		}
		envp++;
	}
	free(key);
	return (i);
}

static int	parse_quote(char const *s, char const **envp, t_list **words)
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
			i += expand_variable(s + i, envp, words);
	}
	return (i + 1);
}

t_token *combine_words(t_list *words)
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
	token = ft_calloc(1, sizeof(token));
	token->value = word;
	token->token = TOKEN_WORD;
	return (token);
}

static int	parse_word(char const *s, char const **envp, t_list **tokens)
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
		if (s[i] == '$')
			i += expand_variable(s + i, envp, &words);
		else if (is_quote(s[i]))
			i += parse_quote(s + i, envp, &words);
		j = i;
		while (s[i] && !is_metachar(s + i) && !is_quote(s[i]))
			i++;
		if (i > j)
			ft_lstadd_back(&words, ft_lstnew(ft_substr(s + j, 0, i - j)));
	}
	if (words)
		ft_lstadd_back(tokens, ft_lstnew(combine_words(words)));
	return (i);
}

static int	parse_operator(char const *s, t_list **tokens)
{
	int	operator_len;

	operator_len = is_operator(s);
	if (!operator_len)
		return (0);
	ft_lstadd_back(tokens, alloc_token(s, operator_len));
	return (operator_len);
}

static t_list	*parse_tokens(char const *s, char const **envp)
{
	t_list		*result;
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
			i += parse_word(s + i, envp, &result);
		}
	}
	return (result);
}

t_list	*tokenize(char *s, char const **envp)
{
	t_list	*result;

	if (!s)
		return (NULL);
	result = parse_tokens(s, envp);
	return (result);
}
