/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_table_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:23:02 by gonische          #+#    #+#             */
/*   Updated: 2024/09/18 17:33:06 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_redirection(int token)
{
	return ((token == TOKEN_IN)
			|| (token == TOKEN_OUT)
			|| (token == TOKEN_INDELIMITER)
			|| (token == TOKEN_OUTAPPEND));
}
