/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:25:50 by gonische          #+#    #+#             */
/*   Updated: 2024/09/08 20:36:27 by gonische         ###   ########.fr       */
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

// Tokens
# define TOKEN_IN			1	// <
# define TOKEN_OUT			2	// >
# define TOKEN_PIPE			3	// |
# define TOKEN_INDELIMITER 	4	// <<
# define TOKEN_OUTAPPEND	5	// >>
# define TOKEN_DOUBLEQUOTE	6 	// ""
# define TOKEN_DOLLARSIGN	7	// $

typedef struct t_token
{
	char	token;
	char	*value;
}	s_token;

typedef struct t_cmd
{
	char	*cmd;
	char	*path;
	s_token *tokens;
}	s_cmd;

/*
	p_parse.c
*/
s_cmd	**parse_input(char *input);

/*
	utils.c
*/
void	print_2dmatrix(const char **matrix);
void	free_2dmatrix(char **matrix);
/*
	grep -i "$(err)" logfile.txt | echo > errors.txt
	cmd flag arg 	in file 	pipe cmd 				out file
	
	We can give for each cmd set of tokens, for example above input will looks like this:
		cmd + tokens[in file -> flag -> arg -> out(pipe)]
		cmd	+ tokens[in(pipe) -> arg -> out file]
	But how to parse $()? 
	< error.txt cat | grep f > $(pwd)/out.txt

	Короч, впизду эту ебаную структуру которую я сделал
	ща захуярим иначе
*/

#endif // MINISHELL_H