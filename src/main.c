/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/09/29 00:40:09 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_loop(char	**envp)
{
	char	*input;
	t_list	*env_list;
	t_cmd	*cmd_list;

	env_list = create_env_list(envp);
	cmd_list = NULL;
	while (true)
	{
		input = readline("minishell-beta$ ");
		if (input && input[0])
		{
			add_history(input);
			cmd_list = parse_input(input, env_list);
			free(input);
		}
		if (input == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		/*
			Put execution here
		*/
		if (cmd_list)
			free_cmd_list(cmd_list);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	setup_signals();
	minishell_loop(envp);
	return (0);
}
