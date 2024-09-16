/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:25:50 by gonische          #+#    #+#             */
/*   Updated: 2024/09/16 17:21:30 by gonische         ###   ########.fr       */
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
# include "limits.h"
# include "../libft/libft.h"

#define SHELL_NAME "Minishell"

# ifndef ARG_MAX
#  define ARG_MAX	1024
# endif

// Tokens
# define TOKEN_UNKNOWN		0
# define TOKEN_IN			1	// <
# define TOKEN_OUT			2	// >
# define TOKEN_PIPE			3	// |
# define TOKEN_INDELIMITER 	4	// <<
# define TOKEN_OUTAPPEND	5	// >>
# define TOKEN_DOUBLEQUOTE	6 	// ""
# define TOKEN_VARIABLE		7	// $
# define TOKEN_SINGLEQUOTE	8	// '
# define TOKEN_WORD			9	// str
typedef struct s_token
{
	char	token;
	char	*value;
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
	struct s_cmd	**cmds;
}	t_shell;

/*
	p_parse.c
*/
t_shell	*parse_input(char *input, t_list *env);

/*
	p_tokenizer.c
*/
t_token	*tokenize(char *s, t_list *env);

/*
	p_tokenizer_utils.c
*/
void	add_token(t_token **list, t_token *token);
t_token	*alloc_token_from_string(char *s);
t_token	*combine_tokenize_words(t_list *words);
int		expand_variable(char const *s, t_list *env, t_list **words);
int		str_to_token_type(const char *s);
void	print_tokens(t_token *tokens); // Temporary function that used only for debugging.

/*
	p_booleans.c
*/
bool	is_space(char c);
bool	is_quote(char c);
int		is_operator(const char *s);
bool	is_metachar(const char *s);
bool	is_word(const char *s);

/*
	p_utils.c
*/
void	clean_memory(t_shell *shell);

/*
	p_cmd_table.c
*/

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
void	display_error(const char **msg, int errnum);

#endif // MINISHELL_H