/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/09/12 11:53:14 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	minishell_loop(char	**envp)
{
	char	*input;

	while (true)
	{
		input = readline("minishell> ");
		if (input)
			parse_input(input, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	minishell_loop(envp);
	// expand_variable("$PWD<", envp);
	return (0);
}
