/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:23:01 by gonische          #+#    #+#             */
/*   Updated: 2024/09/15 15:18:58 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		GLOBAL_SIGNAL = 0;

void	signal_sigint_handler(int signal)
{
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_sigquit_handler(int signal)
{
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, signal_sigint_handler);
	signal(SIGQUIT, signal_sigquit_handler);
}
