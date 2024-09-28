/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:29:05 by gonische          #+#    #+#             */
/*   Updated: 2024/09/29 00:04:52 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"
/*
	TODO: $(), $, $?, $VAR_NAME123, $1, ${13} $((2+2*2)) ;)
*/
int	expand_variable(char *s, char buffer[], int *buffer_index, t_list *env)
{
	int		i;
	char	*key;
	char	*val;
	char	*env_val;

	i = 0;
	while (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_')
		i++;
	key = ft_substr(s, 0, i);
	env_val = get_env(env, key);
	if (env_val)
	{
		val = ft_substr(env_val, i + 1, ft_strlen(env_val + i));
		if (val && *val)
		{
			ft_strncpy(&buffer[*buffer_index], val, ft_strlen(val));
			*buffer_index += ft_strlen(val);
		}
		free(val);
	}
	free(key);
	return (i);
}
