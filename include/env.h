/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 23:49:41 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 02:03:25 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <typedefs.h>
#include <stdlib.h>
#include <stdbool.h>

size_t	get_env_size(t_env *env);
t_env	*env_init(char **envp);
bool	env_push_back(t_env **env, char *key, char *value);
void	free_env_node(t_env *env);
void	destroy_env(t_env **env);

bool	env_is_valid_identifier(const char *str);
t_env	*get_env(t_env *env, const char *key);
char	**env_list_to_array(t_env *env);
void	print_env(t_env *env);
void	print_sorted_env(t_env *env);