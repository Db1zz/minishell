/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:18:25 by gonische          #+#    #+#             */
/*   Updated: 2024/09/19 14:35:22 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*alloc_token(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (ft_printf("Calloc error\n"), NULL); // TODO: put real error handler here
	token->type = type;
	token->value = value;
	return (token);
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

int	skip_spaces(char const *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0); 
	while (is_space(s[i]))
		i++;
	return (i);
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
	else if (s[0] == '<' && s[1] == '<')
		return (TOKEN_INDELIMITER);
	else if (s[0] == '>' && s[1] == '>')
		return (TOKEN_OUTAPPEND);
	else if (s[0] == '<')
		return (TOKEN_IN);
	else if (s[0] == '>')
		return (TOKEN_OUT);
	else if (s[0] == '|')
		return (TOKEN_PIPE);
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
		if (tokens->value)
			ft_printf("%s\n", tokens->value);
		tokens = tokens->next;
	}
}
