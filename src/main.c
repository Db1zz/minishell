/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/12/12 16:06:11 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "p_parsing.h"

void    minishell_loop(char **envp)
{
    char    *input;
    t_list  *env_list;
    t_cmd   *cmd_list;
    t_error e_codes;

    env_list = create_env_list(envp);
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
    rl_clear_history();
    ft_lstclear(&env_list, free);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    setup_signals();
    minishell_loop(envp);
    return (0);
}
