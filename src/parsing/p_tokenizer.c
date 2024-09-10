/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:25:55 by gonische          #+#    #+#             */
/*   Updated: 2024/09/10 18:47:03 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list	*alloc_token(char const *s, size_t len)
{
	t_token	*t;
	t_list	*result;

	t = ft_calloc(1, sizeof(t_token));
	result = ft_lstnew(t);
	t->token = str_to_token_type(s);
	t->value = ft_substr(s, 0, len);
	return (result);
}

static int	parse_quote(char const *s, t_list **tokens)
{
	char		quote;
	char const	*start;

	if (!is_quote(*s))
		return (0);
	quote = *s;
	start = ++s;
	// in this loop we also have to do the variable expansion $
	while (*s && *s != quote)
		s++;
	if (!(*s))
	{
		ft_printf("%s: found unclosed quote.\n", SHELL_NAME);
		return (0); // TODO: Set exit status and exit from parsing.
	}
	ft_lstadd_back(tokens, alloc_token(start, s + 1 - start));
	return (s + 1 - start);
}

static int	parse_operator(char const *s, t_list **tokens)
{
	char const	*start;
	char		*operator;
	char		c;

	if (!*s || !is_operator(s))
		return (0);
	c = s[0];
	start = s;
	while (*s && *s == c)
		s++;
	operator = ft_substr(start, 0, s - start);
	if (operator)
}

/*
	Current task:	Implement quotes
	The problem:
		Metachars are shouldn't be treated as a separators 
		for tokenizer(while in "").
	echo <in"hello, $(USER) :"
*/
static t_list	*parse_tokens(char const *s)
{
	t_list		*result;
	char const	*start;

	result = NULL;
	while (*s)
	{
		while (*s && is_space(*s))
			s++;
		start = s;
		if (*s)
		{
			while (*s && !is_quote(*s) && !is_metachar(s))
				s++;
			if (start != s)
				ft_lstadd_back(&result, alloc_token(start, s - start));
			s += parse_quote(s, &result);
			s += parse_operator(s, &result);
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
