/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/09/20 19:15:27 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_loop(char	**envp)
{
	char	*input;
	t_list	*env_list;
	t_cmd	*cmd_tables;

	env_list = create_env_list(envp);
	cmd_tables = NULL;
	while (true)
	{
		input = readline("minishell-beta$ ");
		if (input && input[0])
		{
			add_history(input);
			cmd_tables = parse_input(input, env_list);
		}
		if (input == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		/*
			Put execution here
		*/
		if (cmd_tables)
			free_cmd_table(cmd_tables);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	setup_signals();
	minishell_loop(envp);
	return (0);
}
