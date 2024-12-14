/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:40:04 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 16:40:19 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include <stdlib.h>

bool	update_value_if_key_exist(t_env *env, char *key, char *value)
{
	t_env	*env_node;

	env_node = get_env(env, key);
	if (env_node)
	{
		if (env_node->value && value != NULL)
		{
			free(env_node->value);
			env_node->value = value;
		}
		if (!env_node->value)
			env_node->value = value;
		return (free(key), true);
	}
	return (false);
}

bool	env_push_back(t_env **env, char *key, char *value)
{
	t_env	*new_env_node;
	t_env	*current;

	if (!env)
		return (false);
	if (update_value_if_key_exist(*env, key, value))
		return (true);
	new_env_node = alloc_env_node(key, value, false);
	if (!*env)
		*env = new_env_node;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new_env_node;
	}
	return (true);
}
