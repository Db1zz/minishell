/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:29:05 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 16:53:59 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"
/*
	TODO: $(), $, $?, $	, $1, ${13} $((2+2*2)) ;)
*/
int	expand_variable(char *s, t_buffer *buffer, t_env *env)
{
	int		i;
	char	*key;
	char	*val;
	t_env	*var;

	i = 0;
	while (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_')
		i++;
	key = ft_substr(s, 0, i);
	var = get_env(env, key);
	if (var)
	{
		val = var->value;
		if (val)
		{
			ft_strncpy(&buffer->array[buffer->index], val, ft_strlen(val));
			buffer->index += ft_strlen(val);
		}
	}
	free(key);
	return (i);
}

int	expand_error_code(t_buffer *buffer, t_error *e_codes)
{
	char	*err_code_str;
	size_t	str_size;

	err_code_str = ft_itoa(e_codes->exit);
	str_size = ft_strlen(err_code_str);
	ft_strncpy(&buffer->array[buffer->index], err_code_str, str_size);
	buffer->index += str_size;
	free(err_code_str);
	return (1);
}
