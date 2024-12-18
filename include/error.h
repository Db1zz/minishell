/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:24:15 by gonische          #+#    #+#             */
/*   Updated: 2024/12/12 15:33:23 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// Error messages
# define MSG_UNCLOSED_QUOTE "Error: found unclosed quote: %c\n"
# define MSG_SYNTAX_ERROR "Error: syntax error near unexpected token: '%s'\n"

typedef int	t_exit_error;

typedef enum e_parsing_error
{
	NO_ERROR,
	ERROR_UNCLOSED_QUOTE,
	ERROR_UNCLOSED_PARENTHESES,
	ERROR_SYNTAX_ERROR,
}	t_parsing_error;

typedef struct s_error
{
	t_parsing_error	parsing;
	t_exit_error	exit;
}	t_error;

#endif // ERROR_H
