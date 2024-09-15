/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/09/15 15:16:12 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <signal.h>

static void	minishell_loop(char	**envp)
{
	char	buffer[100];
	char	*input;
	t_list	*env_list;

	env_list = create_env_list(envp);
	while (true)
	{
		input = readline("minishell-beta$ ");
		if (input)
			parse_input(input, env_list);
		if (input == NULL)
		{
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	setup_signals();
	minishell_loop(envp);
	return (0);
}
