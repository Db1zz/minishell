/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/12/12 17:21:50 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "p_parsing.h"

void	minishell_loop(t_list *env_list)
{
	char	*input;
	t_cmd	*cmd_list;
	t_error	e_codes;

	e_codes.exit = 0;
	cmd_list = NULL;
	while (true)
	{
		input = readline("minishell-beta$ ");
		if (input && input[0])
		{
			add_history(input);
			cmd_list = parse_input(input, env_list, &e_codes);
			if (cmd_list && cmd_list->args && cmd_list->args[0])
				e_codes.exit = execute_cmd(cmd_list, env_list);
			free(input);
		}
		if (input == NULL)
			break ;
		if (cmd_list)
			free_cmd_list(cmd_list);
	}
	(ft_lstclear(&env_list, free), rl_clear_history());
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env_list;

	((void)argc, (void)argv);
	env_list = create_env_list(envp);
	setup_signals();
	minishell_loop(env_list);
	return (0);
}
