/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:36:18 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 01:56:26 by gonische         ###   ########.fr       */
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

t_env	*get_env(t_env *env, const char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	env_push_back(t_env **env, char *key, char *value)
{
	t_env	*new_env_node;
	t_env	*current;

	if (!env)
		return (false);
	new_env_node = ft_calloc(1, sizeof(t_env));
	new_env_node->key = key;
	new_env_node->value = value;
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
