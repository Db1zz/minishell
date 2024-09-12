/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:25:55 by gonische          #+#    #+#             */
/*   Updated: 2024/09/12 14:44:31 by gonische         ###   ########.fr       */
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

static int	parse_quote(char const *s, t_list **tokens)
{
	char		quote;
	char const	*start;

	if (!is_quote(*s))
		return (0);
	quote = *s;
	start = ++s;
	while (*s && *s != quote)
		s++;
	if (!(*s))
	{
		ft_printf("%s: found unclosed quote.\n", SHELL_NAME);
		return (0);
	}
	ft_lstadd_back(tokens, alloc_token(start, s - start));
	return (s + 2 - start);
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

char	*expand_variable(char const *s, char const **envp)
{
	int		i;
	char	*key;
	char	*val;

	if (!s || s[0] != '$')
		return (0);
	i = 0;
	while (s[i] && !is_metachar(s + i + 1))
		i++;
	key = ft_substr(s, 1, i);
	// ft_printf("s == %s, key: %s, i == %d\n", s, 	key, i);
	val = NULL;
	while (*envp)
	{
		if (ft_strncmp(key, *envp, i) == 0)
		{
			val = ft_substr(*envp, i + 1, ft_strlen((*envp) + i + 1));
			break ;
		}
		envp++;
	}
	free(key);
	return (val);
}

/*
	Current task:	Expand Variables
	echo <in"hello, $(USER) :"
*/
static t_list	*parse_tokens(char const *s, char const **envp)
{
	t_list		*result;
	int			i;
	char		*var;

	result = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			while (*s && !is_quote(s[i]) && !is_metachar(s + i))
				i++;
			if (i)
				ft_lstadd_back(&result, alloc_token(s, i));
			s += parse_quote(s, &result);
			s += parse_operator(s, &result);
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
