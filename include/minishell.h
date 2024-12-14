/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:25:50 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 14:01:48 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include "limits.h"
# include "libft.h"
# include "error.h"
# include "typedefs.h"
# include "e_execute.h"
# include "env.h"

// Macro
# define SHELL_NAME "Minishell"
# define ARG_BUFF_SIZE 1024

/*
	parsing functions
*/
t_cmd	*parse_input(char *input, t_env *env, t_error *e_codes);
void	free_cmd_list(t_cmd **cmd_list);

/*
	signal.c
*/
void	setup_signals(void);

/*
	utils.c
*/
void	print_2dmatrix(char const **matrix);
void	free_2dmatrix(char **matrix);
t_shell	*init_shell(char **envp);
void	destroy_shell(t_shell *shell);

/*
	execution
*/
bool	is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
int		execute_external(t_cmd *cmd, t_shell *shell);

#endif // MINISHELL_H