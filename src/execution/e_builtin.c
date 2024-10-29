/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:45:14 by zrz               #+#    #+#             */
/*   Updated: 2024/10/29 20:30:24 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

/*
** get_builtins - Returns the array of builtin commands and their functions
** 
** Returns:
** - Pointer to array of t_builtin structures
*/
static const t_builtin *get_builtins(void)
{
    static const t_builtin builtins[] = {
        {"echo", builtin_echo},
        {"cd", builtin_cd},
        {"pwd", builtin_pwd},
        {"env", builtin_env},
        {"export", builtin_export},
        {"unset", builtin_unset},
        {"exit", builtin_exit},
        {NULL, NULL}
    };
    return (builtins);
}

/*
** is_builtin - Check if a command is a builtin
** @cmd: command name to check
**
** Returns:
** - true if command is a builtin
** - false if command is not a builtin
*/
bool is_builtin(char *cmd)
{
    const t_builtin *builtins;
    int i;

    if (!cmd)
        return (false);

    builtins = get_builtins();
    i = 0;
    while (builtins[i].name)
    {
        if (!ft_strcmp(cmd, builtins[i].name))
            return (true);
        i++;
    }
    return (false);
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
    const t_builtin *builtins;
    int i;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (EXIT_FAILURE);

    builtins = get_builtins();
    i = 0;
    while (builtins[i].name)
    {
        if (!ft_strcmp(cmd->args[0], builtins[i].name))
            return (builtins[i].func(cmd->args, env));
        i++;
    }
    return (EXIT_FAILURE);
}
