/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:36:18 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 16:09:55 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include <stdlib.h>

t_env	*env_init(char **envp)
{
	t_env	*env_list;
	char	*key;
	char	*value;
	size_t	key_len;

	if (!envp || !envp[0])
		return (NULL);
	env_list = NULL;
	while (*envp)
	{
		key_len = ft_strchr(*envp, '=') - *envp;
		key = ft_substr(*envp, 0, key_len);
		value = ft_substr(*envp, key_len + 1, ft_strlen(*envp) - key_len - 1);
		env_push_back(&env_list, key, value);
		envp++;
	}
	return (env_list);
}

t_env	*alloc_env_node(char *key, char *value, bool is_printed)
{
	t_env	*new_env_node;

	new_env_node = ft_calloc(1, sizeof(t_env));
	if (!new_env_node)
		return (NULL);
	new_env_node->is_printed = is_printed;
	new_env_node->key = key;
	new_env_node->value = value;
	return (new_env_node);
}

bool	env_push_back(t_env **env, char *key, char *value)
{
	t_env	*new_env_node;
	t_env	*current;

	if (!env)
		return (false);
	current = get_env(*env, key);
	if (current)
	{
		if (current->value && value != NULL)
		{
			free(current->value);
			current->value = value;
		}
		return (free(key), true);
	}
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

void	free_env_node(t_env *env)
{
	if (env)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
	}
}

void	destroy_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free_env_node(current);
		current = next;
	}
	*env = NULL;
}
