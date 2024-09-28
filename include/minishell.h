/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:25:50 by gonische          #+#    #+#             */
/*   Updated: 2024/09/29 00:33:35 by gonische         ###   ########.fr       */
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
# include "../libft/libft.h"
# include "error.h"

// Macro
# define SHELL_NAME "Minishell"
# define ARG_BUFF_SIZE 1024

// Typedefs
typedef enum s_token_type
{
	T_UNKNOWN,
	T_IN,
	T_OUT,
	T_HEREDOC,
	T_APPEND,
	T_WORD,
	T_PIPE,
	T_AND,
	T_OR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	struct s_token	*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	struct s_token	*tokens;
	struct s_cmd	*cmds;
}	t_shell;

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
/*
	error.c
*/
void	display_error(char *data, t_error error);

#endif // MINISHELL_H