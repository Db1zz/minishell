/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtins.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:18:37 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 15:11:12 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_BUILTINS_H
# define E_BUILTINS_H

# include "minishell.h"
# include "e_execute.h"
# include "typedefs.h"
# include "env.h"
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <linux/limits.h>

char	*get_target_path(char **args, t_env *env);
int		handle_path_error(char **args);
char	*handle_minus(t_env *env);
int		change_dir(const char *path);
void	update_env_var(t_env *env, char *key, char *value);

#endif // E_BUILTINS_H