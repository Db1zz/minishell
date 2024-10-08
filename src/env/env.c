/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:36:18 by gonische          #+#    #+#             */
/*   Updated: 2024/09/29 01:29:11 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env(t_list *env_list, char *key)
{
	size_t	key_len;
	size_t	env_key_len;
	char	*equal_sign;

	if (!key || !key[0] || !env_list)
		return (NULL);
	key_len = ft_strlen(key);
	while (env_list)
	{
		equal_sign = ft_strchr((char *)env_list->content, '=');
		env_key_len = equal_sign - (char *)env_list->content;
		if (env_key_len == key_len &&
				ft_strncmp((char *)env_list->content, key, key_len) == 0)
			return ((char *)env_list->content);
		env_list = env_list->next;
	}
	return (NULL);
}

t_list	*create_env_list(char **envp)
{
	t_list	*env_list;

	if (!envp || !envp[0])
		return (NULL);
	env_list = NULL;
	while (*envp)
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(*envp++)));
	return (env_list);
}
