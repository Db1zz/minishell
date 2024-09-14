/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/09/14 14:11:53 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	minishell_loop(char	**envp)
{
	char	*input;
	t_list	*env_list;

	env_list = create_env_list(envp);
	while (true)
	{
		input = readline("minishell-0.4$ ");
		if (input)
			parse_input(input, env_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	minishell_loop(envp);
	return (0);
}
