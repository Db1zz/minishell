/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/09/16 15:25:06 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_loop(char	**envp)
{
	char	*input;
	t_list	*env_list;
	t_shell	*data;

	env_list = create_env_list(envp);
	while (true)
	{
		input = readline("minishell-beta$ ");
		if (input && input[0])
		{
			add_history(input);
			data = parse_input(input, env_list);
		}
		if (input == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		// execute cmd_table
		clean_memory(data);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	setup_signals();
	minishell_loop(envp);
	return (0);
}
