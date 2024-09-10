/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/09/09 21:18:30 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	minishell_process_input(char *input)
{
	parse_input(input);
}

static void	minishell_loop(char	**envp)
{
	char	*input;

	while (true)
	{
		input = readline("minishell> ");
		if (input)
			minishell_process_input(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	minishell_loop(envp);
	return (0);
}
