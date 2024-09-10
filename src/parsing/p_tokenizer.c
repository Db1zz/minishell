/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:25:55 by gonische          #+#    #+#             */
/*   Updated: 2024/09/09 21:50:24 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	count_tokens(char const *s)
{
	size_t	i;
	size_t	result;
	int		is_word;

	i = 0;
	result = 0;
	is_word = 0;
	while (s[i])
	{
		if ((is_metachar(s + i) || is_space(s[i])) && is_word == 1)
		{
			result++;
			is_word = 0;
		}
		else if (!is_space(s[i]) && is_word == 0)
			is_word = 1;
		i++;
	}
	if (is_word == 1)
		result++;
	return (result);
}

static t_list	*alloc_token(char const *s, size_t len)
{
	t_token	*t;
	t_list	*result;

	t = ft_calloc(1, sizeof(t_token));
		t->token = TOKEN_WORD;
	result = ft_lstnew(t);
	t->token = str_to_token_type(s);
	t->value = ft_substr(s, 0, len);
	return (result);
}

static t_list	*parse_tokens(char const *s)
{
	t_list		*result;
	char const	*start;
	int			c;

	result = NULL;
	while (*s)
	{
		while (*s && is_space(*s))
			s++;
		start = s;
		if (*s)
		{
			c = is_metachar(s);
			if (c)
				s += c;
			else
				while (*s && (!is_space(*s) && !is_metachar(s)))
					s++;
			ft_lstadd_back(&result, alloc_token(start, s - start));
		}
	}
	return (result);
}

t_list	*tokenize(char *s)
{
	t_list	*result;

	if (!s)
		return (NULL);
	result = parse_tokens(s);
	return (result);
}
