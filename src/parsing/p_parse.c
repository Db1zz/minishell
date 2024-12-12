/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:24:24 by gonische          #+#    #+#             */
/*   Updated: 2024/12/12 16:40:09 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

int	parse_expansion(char *str, t_buffer *buffer, t_list *env, t_error *e_codes)
{	
	int	i;

	i = 1;
	if ((str[0] != '$'))
		return (0);
	if (ft_isalpha(str[i]) || str[i] == '_')
		i += expand_variable(str + i, buffer, env);
	else if (str[i] == '?')
		i += expand_error_code();
	else
		buffer->array[buffer->index++] = '$';
	return (i);
}

int	parse_quote(char *str, t_buffer *buffer, t_list *env, t_error *e_codes)
{
	char	quote;
	int		i;

	i = 1;
	quote = str[0];
	while (str[i] && quote)
	{
		if (str[i] == '$' && quote == '\"')
			i += parse_expansion(str + i, buffer, env, e_codes);
		else if (str[i] != quote)
			buffer->array[buffer->index++] = str[i++];
		else
		{
			quote = '\0';
			i++;
		}
	}
	if (quote)
	{
		e_codes->parsing = ERROR_UNCLOSED_QUOTE;
		ft_dprintf(STDERR_FILENO, MSG_UNCLOSED_QUOTE, quote);
	}
	return (i);
}

int	parse_word(char *str, t_buffer *buffer, t_list *env, t_error *e_codes)
{
	int	i;

	i = 0;
	while (str[i] && !is_metachar(str + i) && e_codes->parsing == NO_ERROR)
	{
		if (is_quote(str[i]))
			i += parse_quote(str + i, buffer, env, e_codes);
		else if (str[i] == '$')
			i += parse_expansion(str + i, buffer, env, e_codes);
		else
			buffer->array[buffer->index++] = str[i++];
	}
	buffer->array[buffer->index] = '\0';
	return (i);
}

int	parse_operator(char *str, t_buffer *buffer)
{
	int	operator_len;
	int	i;

	i = 0;
	operator_len = is_operator(str);
	if (!operator_len)
		return (0);
	while (i < operator_len)
		buffer->array[buffer->index++] = str[i++];
	buffer->array[buffer->index] = '\0';
	return (i);
}

t_cmd	*parse_input(char *input, t_list *env, t_error *e_codes)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	if (!input)
		return (NULL);
	e_codes->parsing = NO_ERROR;
	cmd_list = NULL;
	tokens = tokenizer(input, env, e_codes);
	if (tokens && !e_codes->parsing)
		cmd_list = build_cmd_list(tokens, e_codes);
	if (e_codes->parsing)
	{
		free_cmd_list(cmd_list);
		cmd_list = NULL;
	}
	print_cmd_list(cmd_list); // Debug Only
	return (free_tokens(tokens), cmd_list);
}
