/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:12:47 by zrz               #+#    #+#             */
/*   Updated: 2024/11/15 15:40:23 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

int execute_cmd(t_cmd *cmd, t_list *env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (EXIT_SUCCESS);
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd,env));
	else
		return (execute_external(cmd, env));
}
/*
	main entry point for command execution,
	which then delegates to either builtin or external command handling.
*/