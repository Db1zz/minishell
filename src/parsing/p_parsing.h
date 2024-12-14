/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parsing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:46:20 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 14:01:17 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_PARSING_H
# define P_PARSING_H

# include "../../include/minishell.h"

typedef struct s_buffer
{
	char	array[ARG_BUFF_SIZE];
	int		index;
}	t_buffer;

/*
	p_parse.c
*/
int				parse_expansion(char *str, t_buffer *buffer,
					t_env *env, t_error *e_codes);
int				parse_quote(char *str, t_buffer *buffer,
					t_env *env, t_error *e_codes);
int				parse_word(char *str, t_buffer *buffer,
					t_env *env, t_error *e_codes);
int				parse_operator(char *str, t_buffer *buffer);
t_cmd			*parse_input(char *input, t_env *env, t_error *e_codes);

/*
	p_parse_helpers.c
*/
bool			is_space(char c);
bool			is_quote(char c);
int				is_operator(const char *s);
bool			is_metachar(const char *s);
bool			is_word(const char *s);

/*
	p_expansion.c
*/
int				expand_variable(char *s, t_buffer *buffer, t_env *env);
int				expand_error_code(t_buffer *buffer, t_error *e_codes);

/*
	p_token.c
*/
t_token			*alloc_token(t_token_type type, char *value);
void			add_token(t_token **list, t_token *token);
t_token			*tokenizer(char *input, t_env *env, t_error *error);
bool			is_redirection(t_token *token);
bool			is_cmd_spearator(t_token *token);

/*
	p_cmd_list.c
*/
t_cmd			*build_cmd_list(t_token *tokens, t_error *error);

/*
	p_mem_cleaner.c
*/
void			free_cmd_list(t_cmd **cmd_list);
void			free_tokens(t_token *tokens);

// =========================== DEBUG ONLY =========================== //
void			print_tokens(t_token *tokens);
void			print_cmd_list(t_cmd *cmd_table);

/*
	p_parse_utils.c
*/
t_token_type	str_to_token_type(const char *s);
int				skip_spaces(char const *s);

#endif // P_PARSING_H