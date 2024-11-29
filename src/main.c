/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:22:53 by gonische          #+#    #+#             */
/*   Updated: 2024/11/28 15:33:37 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    minishell_loop(char **envp)
{
    char    *input;
    t_list  *env_list;
    t_cmd   *cmd_list;
    int     status;

    env_list = create_env_list(envp);
    cmd_list = NULL;
    while (true)
    {
        input = readline("minishell-beta$ ");
        if (input && input[0])
        {
            add_history(input);
            cmd_list = parse_input(input, env_list);
            if (cmd_list && cmd_list->args && cmd_list->args[0])
                execute_cmd(cmd_list, env_list);
            free(input);
        }
        if (input == NULL)
        {
            ft_printf("exit\n");
            break;
        }
        if (cmd_list)
            free_cmd_list(cmd_list);
    }
    rl_clear_history();
    ft_lstclear(&env_list, free);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	setup_signals();
// 	minishell_loop(envp);
// 	return (0);
// }

void test_builtins(t_list *env)
{
    // Test echo
    char *echo_args1[] = {"echo", "hello", "world", NULL};
    char *echo_args2[] = {"echo", "-n", "hello", NULL};
    t_cmd echo_cmd1 = {.args = echo_args1, .redirections = NULL, .next = NULL};
    t_cmd echo_cmd2 = {.args = echo_args2, .redirections = NULL, .next = NULL};
    
    ft_printf("\n=== Testing echo ===\n");
    execute_builtin(&echo_cmd1, env);  // Should print: hello world\n
    execute_builtin(&echo_cmd2, env);  // Should print: hello (no newline) - NEEDS FIX
    ft_printf("\n");  // Add newline for clarity

    // Test pwd
    char *pwd_args[] = {"pwd", NULL};
    t_cmd pwd_cmd = {.args = pwd_args, .redirections = NULL, .next = NULL};
    
    ft_printf("\n=== Testing pwd ===\n");
    execute_builtin(&pwd_cmd, env);

    // Test cd
    char *cd_args[] = {"cd", "..", NULL};
    t_cmd cd_cmd = {.args = cd_args, .redirections = NULL, .next = NULL};
    
    ft_printf("\n=== Testing cd ===\n");
    ft_printf("Before cd:\n");
    execute_builtin(&pwd_cmd, env);
    execute_builtin(&cd_cmd, env);
    ft_printf("After cd:\n");
    execute_builtin(&pwd_cmd, env);

    // Test env
    char *env_args[] = {"env", NULL};
    t_cmd env_cmd = {.args = env_args, .redirections = NULL, .next = NULL};
    
    ft_printf("\n=== Testing env ===\n");
    execute_builtin(&env_cmd, env);
}

void test_external_commands(t_list *env)
{
    // Test existing command
    char *ls_args[] = {"ls", "-l", NULL};
    t_cmd ls_cmd = {.args = ls_args, .redirections = NULL, .next = NULL};
    
    ft_printf("\n=== Testing ls -l ===\n");
    execute_external(&ls_cmd, env);

    // Test non-existent command
    char *fake_args[] = {"nonexistent", NULL};
    t_cmd fake_cmd = {.args = fake_args, .redirections = NULL, .next = NULL};
    
    ft_printf("\n=== Testing non-existent command ===\n");
    execute_external(&fake_cmd, env);

    // Test command with full path
    char *path_args[] = {"/bin/echo", "hello", NULL};
    t_cmd path_cmd = {.args = path_args, .redirections = NULL, .next = NULL};
    
    ft_printf("\n=== Testing command with full path ===\n");
    execute_external(&path_cmd, env);
}

// In your main or a separate test function:
void run_tests(char **envp)
{
    t_list *env;
    
    env = create_env_list(envp);
    if (!env)
        return;

    ft_printf("\n=== Starting Tests ===\n");
    
    test_builtins(env);
    test_external_commands(env);
    
    ft_printf("\n=== Tests Complete ===\n");
    
    ft_lstclear(&env, free);
}
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    // Run tests first
    // run_tests(envp);

    // Then run your normal shell
    setup_signals();
    minishell_loop(envp);
    return (0);
}