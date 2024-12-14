/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:16:10 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 01:57:43 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

static void	reset_printed_states(t_env *env)
{
	while (env)
	{
		env->is_printed = false;
		env = env->next;
	}
}

static t_env *get_smallest_available_env(t_env *env)
{
	t_env	*current;
	t_env	*smallest_env;

	current = env;
	smallest_env = NULL;
	while (current)
	{
		if (!current->is_printed)
		{
			if (smallest_env == NULL)
			{
				smallest_env = current;
				continue ;
			}
			if (ft_strcmp(smallest_env->key, current->key) > 0)
				smallest_env = current;
		}
		current = current->next;
	}
	return (smallest_env);
}

void	print_sorted_env(t_env *env)
{
	int		counter;
	t_env	*to_print;

	counter = get_env_size(env);
	if (counter == 0)
		return ;
	while (counter)
	{
		to_print = get_smallest_available_env(env);
		if (to_print)
		{
			to_print->is_printed = true;
			if (to_print->key && to_print->value)
				printf("declare -x %s=\"%s\"\n", to_print->key, to_print->value);
			else
				printf("declare -x %s\n", to_print->key);
		}
		counter--;
	}
	reset_printed_states(env);
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
