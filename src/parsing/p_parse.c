/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:40:56 by gonische          #+#    #+#             */
/*   Updated: 2024/09/12 00:28:09 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	**parse_input(char *input, char **envp)
{
	// s_cmd	*cmd_table[ARG_MAX]; // Temporary
	// s_cmd	**result;
	t_list		*tokens;

	if (!input)
		return (NULL);
	// result = NULL;
	tokens = tokenize(input, envp);
	print_tokens(tokens);
	free (input);
	return (NULL); // TODO
}
