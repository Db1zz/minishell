/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parsing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:46:20 by gonische          #+#    #+#             */
/*   Updated: 2024/09/20 19:00:52 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../include/minishell.h"

/*
	p_parse.c
*/
t_cmd	*parse_input(char *input, t_list *env);

/*
	p_parse_utils.c
*/
char			*combine_words(t_list *words);
t_token_type	str_to_token_type(const char *s);
int				skip_spaces(char const *s);

/*
	p_parse_helpers.c
*/
bool	is_space(char c);
bool	is_quote(char c);
int		is_operator(const char *s);
bool	is_metachar(const char *s);
bool	is_word(const char *s);

/*
	p_var_expander.c
*/
int	expand_variable(char const *s, t_list *env, t_list **words);

/*
	p_token.c
*/
t_token	*alloc_token(t_token_type type, char *value);
void	add_token(t_token **list, t_token *token);
t_token	*dup_token(t_token *token);
bool	is_redirection(t_token *token);
bool	is_cmd_spearator(t_token *token);
// =========================== DEBUG ONLY =========================== //
void	print_tokens(t_token *tokens);

/*
	p_cmd_table.c
*/
t_cmd	*build_cmd_table(t_token *tokens);
// =========================== DEBUG ONLY =========================== //
void	print_cmd_table(t_cmd *cmd_table);

/*
	p_mem_cleaner.c
*/
void	free_cmd_table(t_cmd *cmd_table);
void	free_tokens(t_token *tokens);
void	clean_memory(t_cmd *cmd_table, t_token *tokens);

#endif // PARSING_H
