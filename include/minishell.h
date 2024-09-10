/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:25:50 by gonische          #+#    #+#             */
/*   Updated: 2024/09/10 18:22:17 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "limits.h"
# include "../libft/libft.h"

#define SHELL_NAME "Minishell"

# ifndef ARG_MAX
#  define ARG_MAX	131072
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
# define TOKEN_FLAG			10	// -FLAG

typedef struct s_token
{
	char	token;
	char	*value;
}	t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	*path;
	t_token	*arg[ARG_MAX];
	int		in;
	int		out;
	int		err;
}	t_cmd;

/*
	p_parse.c
*/
t_cmd	**parse_input(char *input);

/*
	p_tokenizer.c
*/
t_list	*tokenize(char *s);

/*
	p_utils.c
*/
void	print_tokens(t_list *lst);
int		str_to_token_type(const char *s);
/*
	p_booleans.c
*/
bool	is_space(char c);
bool	is_quote(char c);
bool	is_operator(const char *s);
bool	is_metachar(const char *s);

/*
	utils.c
*/
void	print_2dmatrix(const char **matrix);
void	free_2dmatrix(char **matrix);

#endif // MINISHELL_H