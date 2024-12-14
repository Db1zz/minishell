/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:31:54 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 00:01:24 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void	print_2dmatrix(char const **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		ft_printf("%s\n", matrix[i++]);
}

void	free_2dmatrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = env_init(envp);
	setup_signals();
	return (shell);
}

void	destroy_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmds)
		free_cmd_list(shell->cmds);
	if (shell->env)
		destroy_env(&shell->env);
	if (shell->input)
		free(shell->input);
	rl_clear_history();
	free(shell);
}
