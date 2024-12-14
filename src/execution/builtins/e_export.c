/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 23:26:48 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 15:00:53 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "e_execute.h"
#include "env.h"

static char	*env_extract_key(const char *env_var)
{
	char	*key;

	if (!env_var)
		return (NULL);
	key = ft_strchr(env_var, '=');
	if (!key)
		return (NULL);
	return (ft_substr(env_var, 0, key - env_var));
}

static char	*env_extract_value(const char *env_var, const char *key)
{
	char	*value;
	size_t	key_lenght;
	
	if (!env_var || !key)
		return (NULL);
	key_lenght = ft_strlen(key);
	if (!*(env_var + key_lenght))
		return (NULL);
	value = ft_substr(env_var, key_lenght + 1, key - env_var - 1);
	return (value);
}

static int	check_asign_key(char *arg, t_env **env)
{
	char	*key;
	char	*value;
	int		status;

	key = NULL;
	value = NULL;
	status = EXIT_SUCCESS;
	if (!arg)
		return (EXIT_FAILURE);
	key = env_extract_key(arg);
	if (!key)
		key = ft_strdup(arg);
	if (env_is_valid_identifier(key))
	{
		value = env_extract_value(arg, key);
		env_push_back(env, key, value);
	}
	else if (key)
	{
		ft_dprintf(STDERR_FILENO, "export: %s: not a valid identifier\n", key);
		free(key);
		status = EXIT_FAILURE;
	}
	return (status);
}

int	builtin_export(char **args, t_shell *shell)
{
	t_env	*env;
	int		i;
	int		status;

	env = shell->env;
	i = 0;
	status = EXIT_SUCCESS;
	if (!args[1])
	{
		print_sorted_env(shell->env);
		return (status);
	}
	while (args[++i])
		status = check_asign_key(args[i], &shell->env);
	return (status);
}
