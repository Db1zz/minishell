/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:40:56 by gonische          #+#    #+#             */
/*   Updated: 2024/09/17 16:54:26 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
