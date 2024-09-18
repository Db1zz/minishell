/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:29:05 by gonische          #+#    #+#             */
/*   Updated: 2024/09/18 13:29:27 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h" 

/**
 * expand_variable - Expands a variable from the string using the environment variables.
 * 
 * @param s: The string containing the variable, starting with a '$' character.
 * @param envp: An array of environment variables for variable expansion.
 * @param words: A list to which the expanded variable's value will be added.
 * 
 * This function parses a variable name from the string `s` after the `$` symbol and
 * searches for its value in the `envp` array. If a match is found, the value is appended
 * to the `words` list. The function handles both variable expansion and partial parsing
 * of the input string.
 * 
 * @return i: The number of characters processed in the input string.
 */

int	expand_variable(char const *s, t_list *env, t_list **words)
{
	int		i;
	char	*key;
	char	*val;
	char	*env_val;

	if (!s || s[0] != '$')
		return (0);
	if (s[1] && ft_isdigit(s[1]))
		return (2);
	i = 1;
	while (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_')
		i++;
	if (i == 1)
		return (ft_lstadd_back(words, ft_lstnew(ft_substr("$", 0, 1))), 1);
	key = ft_substr(s, 1, i - 1);
	env_val = get_env(env, key);
	if (env_val)
	{
		val = ft_substr(env_val, i, ft_strlen(env_val + i));
		if (val)
			ft_lstadd_back(words, ft_lstnew(val));
	}
	return (free(key), i);
}
