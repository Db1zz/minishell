/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:29 by gonische          #+#    #+#             */
/*   Updated: 2024/11/27 14:18:04 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

static size_t	count_args(t_token *tokens)
{
	size_t	result;

	result = 0;
	while (tokens && !is_cmd_spearator(tokens))
	{
		if (!is_redirection(tokens))
			result++;
		tokens = tokens->next;
	}
	return (result);
}

static t_token *get_redirection(t_token **tokens, t_error *error)
{
	t_token	*redirection;
	char	*err_msg_val;

	redirection = ft_calloc(1, sizeof(t_token));
	redirection->type = (*tokens)->type;
	if (!(*tokens)->next || (*tokens)->next->type != T_WORD)
	{
		*error = ERROR_SYNTAX_ERROR;
		if ((*tokens)->next)
			err_msg_val = (*tokens)->next->value;
		else
			err_msg_val = "newline";
		ft_dprintf(STDERR_FILENO, MSG_SYNTAX_ERROR, err_msg_val);
		free(redirection);
		return (NULL);
	}
	(*tokens) = (*tokens)->next;
	redirection->value = ft_strdup((*tokens)->value);
	return (redirection);
}

static t_cmd	*extract_cmd(t_token **tokens, t_error *error)
{
	const size_t	args_size = count_args(*tokens);
	t_cmd			*cmd;
	int				arg_index;
	
	arg_index = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->args = ft_calloc(args_size + 1, sizeof(char *));
	while ((*tokens) && !is_cmd_spearator(*tokens) && !*error)
	{
		if (is_redirection(*tokens))
			add_token(&cmd->redirections, get_redirection(tokens, error));
		else
			cmd->args[arg_index++] = ft_strdup((*tokens)->value);
		(*tokens) = (*tokens)->next;
	}
	if (is_cmd_spearator(*tokens))
		*tokens = (*tokens)->next;
	return (cmd);
}

t_cmd	*build_cmd_list(t_token *tokens, t_error *error)
{
	t_cmd	*cmd_list;
	t_cmd	*last_cmd;
	t_cmd	*cmd;

	if (!tokens)
		return (NULL);
	cmd_list = NULL;
	while (tokens && !*error)
	{
		cmd = extract_cmd(&tokens, error);
		if (!cmd_list)
			cmd_list = cmd;
		else
			last_cmd->next = cmd;
		last_cmd = cmd;
	}
	return (cmd_list);
}

// =========================== DEBUG ONLY =========================== //
/**
 * print_cmd_list - Debug function to print the command table.
 * 
 * @param cmd_table: The command table to print.
 * 
 * This function prints the arguments and redirections for each 
 * command in the command table.
 * 
 * @return void
 */
void	print_cmd_list(t_cmd *cmd_table)
{
	int		i;
	t_token	*redirections;

	while (cmd_table)
	{
		i = 0;
		redirections = cmd_table->redirections;
		ft_printf("Args: ");
		while (cmd_table->args && cmd_table->args[i])
			ft_printf("[%s]", cmd_table->args[i++]);
		ft_printf("\nRedirections: ");
		while (redirections)
		{
			ft_printf("[%s %d]", redirections->value, redirections->type);
			redirections = redirections->next;
		}
		ft_printf("\n");
		ft_printf("--------------------------\n");
		cmd_table = cmd_table->next;
	}
}
