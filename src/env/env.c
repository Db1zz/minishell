/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:36:18 by gonische          #+#    #+#             */
/*   Updated: 2024/09/14 14:15:49 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*get_env(t_list *env_list, char *key)
{
	size_t	key_len;

	if (!key || !key[0] || !env_list)
		return (NULL);	
	key_len = ft_strlen(key);
	while (env_list)
	{
		if (ft_strncmp((char *)env_list->content, key, key_len) == 0)
			return (env_list);
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
		ft_lstadd_back(&env_list, ft_lstnew(*envp++));
	return (env_list);
}
