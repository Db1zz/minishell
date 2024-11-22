/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execute.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:14:19 by zrz               #+#    #+#             */
/*   Updated: 2024/11/22 21:58:31 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_EXECUTE_H
# define E_EXECUTE_H

# include "../../include/minishell.h"
# include <sys/types.h> // pid_t
# include <sys/wait.h>	//waitpid, WEXITSTATUS
# include <fcntl.h>

// error messages matching those of bash
# define MSG_CD_USAGE "cd: too many arguments\n"
# define MSG_CD_ERROR "cd: %s: %s\n"
# define MSG_PWD_ERROR "pwd: error retrieving current directory: %s\n"
# define MSG_ENV_ERROR "env: %s\n"
# define MSG_EXPORT_ERROR "export: '%s': not a valid identifier\n"
# define MSG_UNSET_ERROR "unset: '%s': not a valid identifier\n"



// Exit Status Codes (matching bash behavior)
# define EXIT_SUCCESS 0      // Successful execution
# define EXIT_FAILURE 1      // General errors
# define EXIT_MISUSE 2       // Builtin misuse
# define EXIT_NOT_FOUND 127  // Command not found


// Function type for builtin commands
typedef int (*t_builtin_func)(char **args, t_list *env);

// Built in comman struct
// maps cmds to their implementation to be + simple
typedef struct	s_builtin
{
    char			*name;
    t_builtin_func	func;
}	t_builtin;


/* Prototypes */

// main exec
int		execute_cmd(t_cmd *cmd, t_list *env);

// Path handling function (used by external execution)
char	*find_cmd_path(char *cmd, t_list *env);

// Builtin command functions
/* 
	the prototypes follow the same structure for simplicity,
	when not needed, env set to void
*/
int builtin_echo(char **args, t_list *env);
int builtin_cd(char **args, t_list *env);
int builtin_pwd(char **args, t_list *env);
int builtin_env(char **args, t_list *env);
int builtin_export(char **args, t_list *env);
int builtin_unset(char **args, t_list *env);
int builtin_exit(char **args, t_list *env);

// Builtin utilities
//int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_list *env);

// redirections
int	setup_redirections(t_token *redirections);

#endif // EXECUTE_H