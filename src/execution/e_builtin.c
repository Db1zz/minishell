/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:45:14 by zrz               #+#    #+#             */
/*   Updated: 2024/11/18 17:06:57 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

/*
** get_builtins - Returns the array of builtin commands and their functions
** 
** Returns:
** - Pointer to array of t_builtin structures
*/
static void fill_builtin_array(t_builtin *builtins)
{
    builtins[0] = (t_builtin){"echo", builtin_echo};
    builtins[1] = (t_builtin){"cd", builtin_cd};
    builtins[2] = (t_builtin){"pwd", builtin_pwd};
    builtins[3] = (t_builtin){"env", builtin_env};
    builtins[4] = (t_builtin){"export", builtin_export};
    builtins[5] = (t_builtin){"unset", builtin_unset};
    builtins[6] = (t_builtin){"exit", builtin_exit};
    builtins[7] = (t_builtin){NULL, NULL};
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
    t_builtin builtins[8];
    int       i;

    if (!cmd)
        return (false);
    
    fill_builtin_array(builtins);
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
    t_builtin builtins[8];
    int       i;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (EXIT_FAILURE);

    fill_builtin_array(builtins);
    i = 0;
    while (builtins[i].name)
    {
        if (!ft_strcmp(cmd->args[0], builtins[i].name))
            return (builtins[i].func(cmd->args, env));
        i++;
    }
    return (EXIT_FAILURE);
}


// int execute_builtin(t_cmd *cmd, t_list *env)
// {
// 	const t_builtin	*builtins;
// 	int				i;

// 	if (!cmd || !cmd->args || !cmd->args[0])
// 		return (EXIT_FAILURE);

// 	builtins = get_builtin();
// 	i = 0;
// 	while (builtins[i].name)
// 	{
// 		if (!strcmp(cmd->args[0], builtins[i].name))
// 			return (builtins[i].func(cmd->args, env));
// 		i++;
// 	}
// 	return (EXIT_FAILURE);
// }
