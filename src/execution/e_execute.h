/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execute.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:14:19 by zrz               #+#    #+#             */
/*   Updated: 2024/12/13 15:59:30 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_EXECUTE_H
# define E_EXECUTE_H

# include "../../include/typedefs.h"
# include "libft.h"
# include <sys/types.h> // pid_t
# include <sys/wait.h>	//waitpid, WEXITSTATUS
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>

// error messages matching those of bash
# define MSG_CD_USAGE "cd: too many arguments\n"
# define MSG_CD_ERROR "cd: %s: %s\n"
# define MSG_PWD_ERROR "pwd: error retrieving current directory: %s\n"
# define MSG_ENV_ERROR "env: %s\n"
# define MSG_EXPORT_ERROR "export: '%s': not a valid identifier\n"
# define MSG_UNSET_ERROR "unset: '%s': not a valid identifier\n"

// Exit Status Codes (matching bash behavior)
# define EXIT_SUCCESS 0       	// Successful execution
# define EXIT_FAILURE 1       	// General errors
# define EXIT_MISUSE 2        	// Builtin misuse
# define EXIT_ENV_ERROR 125		// env-specific errors (GNU coreutils behavior)
# define EXIT_CMD_NOT_EXEC 126 	// Missing execute permissions
# define EXIT_NOT_FOUND	127 // Command or dir not found
# define EXIT_RANGE 128 		// Valid range of exit argument is from 0 to 255
# define EXIT_TERMINATED 130  	// Control C was pressed to end script / exec
# define EXIT_UNDEFINED 255		// Status not defined

// Permisions
# define FILE_PERMISSIONS 0644

// Function type for builtin commands
typedef int	(*t_builtin_func)(char **args, t_list *env);

// Built in comman struct
// maps cmds to their implementation to be + simple
typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}	t_builtin;

/* Prototypes */

// main exec
int		execute_cmd(t_cmd *cmd, t_list *env);
int		execute_external(t_cmd *cmd, t_list *env);

// Path handling function (used by external execution)
char	*find_cmd_path(char *cmd, t_list *env);

// Builtin command functions
/* 
	the prototypes follow the same structure for simplicity,
	when not needed, env set to void
*/
int		builtin_echo(char **args, t_list *env);
int		builtin_cd(char **args, t_list *env);
int		builtin_pwd(char **args, t_list *env);
int		builtin_env(char **args, t_list *env);
int		builtin_export(char **args, t_list *env);
int		builtin_unset(char **args, t_list *env);
int		builtin_exit(char **args, t_list *env);
bool	is_builtin(char *cmd);

// Builtin utilities
//int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_list *env);

// redirections
typedef struct s_redir_data
{
	int	fds[2];
}	t_redir_data;

int		setup_redirections(t_token *redirections);
int		heredoc_redirection(const char *delimiter);

// pipes
int		execute_pipeline(t_cmd *cmd_list, t_list *env);
int		exec_pipe_cmds(t_cmd *cmd_list, t_list *env,
			int pipes[2][2], int cmd_count);
void	close_pipes(int cmd_count, int pipes[2][2]);

#endif // EXECUTE_H