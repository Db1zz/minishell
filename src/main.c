/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 15:57:49 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "p_parsing.h"
#include "env.h"

void	minishell_loop(t_shell *shell)
{
	t_error	e_codes;

	e_codes.exit = 0;
	while (true)
	{
		shell->input = readline("minishell-beta$ ");
		if (shell->input && shell->input[0])
		{
			add_history(shell->input);
			shell->cmds = parse_input(shell->input, shell->env, &e_codes);
			if (shell->cmds && shell->cmds->args && shell->cmds->args[0])
				e_codes.exit = execute_cmd(shell);
			free(shell->input);
		}
		if (shell->input == NULL)
			break ;
		if (shell->cmds)
			free_cmd_list(&shell->cmds);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	((void)argc, (void)argv);
	shell = init_shell(envp);
	minishell_loop(shell);
	destroy_shell(shell);
	shell = NULL;
	return (0);
}
