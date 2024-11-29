/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:25:50 by gonische          #+#    #+#             */
/*   Updated: 2024/11/28 15:41:36 by jroseiro         ###   ########.fr       */
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

// Macro
# define SHELL_NAME "Minishell"
# define ARG_BUFF_SIZE 1024

/*
	parsing functions
*/
t_cmd	*parse_input(char *input, t_list *env);
void	free_cmd_list(t_cmd *cmd_list);

/*
	signal.c
*/
void	setup_signals(void);

/*
	utils.c
*/
void	print_2dmatrix(char const **matrix);
void	free_2dmatrix(char **matrix);

/*
	env.c
*/
char	*get_env(t_list *env_list, char *key);
t_list	*create_env_list(char **envp);
char	**env_list_to_array(t_list *env);
/*
	error.c
*/
void	display_error(char *data, t_error error);

/*
	execution
*/
bool	is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_list *env);
int		execute_external(t_cmd *cmd, t_list *env);

#endif // MINISHELL_H