/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:45:14 by zrz               #+#    #+#             */
/*   Updated: 2024/10/28 14:37:54 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

//table of built in cmds
static const t_builtin g_builtins[] = {
    {"echo", builtin_echo},
    {"cd", builtin_cd},
    {"pwd", builtin_pwd},
    {"env", builtin_env},
    {"export", builtin_export},
    {"unset", builtin_unset},
    {"exit", builtin_exit},
    {NULL, NULL}
};


/*
** is_builtin - Check if a command is a builtin
** @cmd: command name to check
**
** Returns:
** - 1 if command is a builtin
** - 0 if command is not a builtin
*/
int is_builtin(char *cmd)
{
    int i;

    if (!cmd)
        return (0);
        
    i = 0;
    while (g_builtins[i].name)
    {
        if (!ft_strcmp(cmd, g_builtins[i].name))
            return (1);
        i++;
    }
    return (0);
}

/*
** execute_builtin - Execute builtin commands
** @cmd: command structure containing args and redirections
** @env: environment variables list
**
** Returns:
** - Exit status of the builtin command (0 for success)
** - EXIT_FAILURE if command not found or error
*/
int execute_builtin(t_cmd *cmd, t_list *env)
{
    int i;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (EXIT_FAILURE);

    i = 0;
    while (g_builtins[i].name)
    {
        if (!ft_strcmp(cmd->args[0], g_builtins[i].name))
            return (g_builtins[i].func(cmd->args, env));
        i++;
    }
    return (EXIT_FAILURE);
}
