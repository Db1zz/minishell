/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:24:24 by gonische          #+#    #+#             */
/*   Updated: 2024/12/06 15:06:08 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

int	parse_expansion(char *str, char buffer[], int *buffer_index, t_list *env)
{	
	int	i;

	i = 1;
	if ((str[0] != '$'))
		return (0);
	if (ft_isalpha(str[i]) || str[i] == '_')
		i += expand_variable(str + i, buffer, buffer_index, env);
	else
		buffer[(*buffer_index)++] = '$';
	return (i);
}

int	parse_quote(char *str, char buffer[], int *buff_index, t_list *env, 
		t_error *error)
{
	char	quote;
	int		i;

	i = 1;
	quote = str[0];
	while (str[i] && quote)
	{
		if (str[i] == '$' && quote == '\"')
			i += parse_expansion(str + i, buffer, buff_index, env);
		else if (str[i] != quote)
			buffer[(*buff_index)++] = str[i++];
		else
		{
			quote = '\0';
			i++;
		}
	}
	if (quote)
	{
		*error = ERROR_UNCLOSED_QUOTE;
		ft_dprintf(STDERR_FILENO, MSG_UNCLOSED_QUOTE, quote);
	}
	return (i);
}

int	parse_word(char *str, char buffer[], int *buff_index, t_list *env,
		t_error *error)
{
	int	i;

	i = 0;
	while (str[i] && !is_metachar(str + i) && *error == NO_ERROR)
	{
		if (is_quote(str[i]))
			i += parse_quote(str + i, buffer, buff_index, env, error);
		else if (str[i] == '$')
			i += parse_expansion(str + i, buffer, buff_index, env);
		else
			buffer[(*buff_index)++] = str[i++];
	}
	buffer[(*buff_index)] = '\0';
	return (i);
}

int	parse_operator(char *str, char buffer[], int *buff_index)
{
	int	operator_len;
	int	i;

	i = 0;
	operator_len = is_operator(str);
	if (!operator_len)
		return (0);
	while (i < operator_len)
		buffer[(*buff_index)++] = str[i++];
	buffer[(*buff_index)] = '\0';
	return (i);
}

t_cmd	*parse_input(char *input, t_list *env)
{
	t_token	*tokens;
	t_cmd	*cmd_list;
	t_error	error;

	if (!input)
		return (NULL);
	error = NO_ERROR;
	cmd_list = NULL;
	tokens = tokenizer(input, env, &error);
	if (tokens && !error)
		cmd_list = build_cmd_list(tokens, &error);
	if (error)
	{
		free_cmd_list(cmd_list);
		cmd_list = NULL;
	}
	// Debug only
	// print_tokens(tokens);
	print_cmd_list(cmd_list);
	//
	free_tokens(tokens);
	return (cmd_list); // TODO
}
