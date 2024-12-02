/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:45:40 by zrz               #+#    #+#             */
/*   Updated: 2024/12/02 14:43:24 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

static int input_redirection(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, FILE_PERMISSIONS);
	if (fd < 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", 
			file, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

/*
** The general format for redirecting input is: [n]<word
**
** The general format for redirecting output is: [n]>[|]word
**
*/
static int	output_redirection(char *file, bool to_append)
{
	int fd;
	int flags;

	flags = O_WRONLY | O_CREAT;
	if (to_append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, FILE_PERMISSIONS);
	if (fd < 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", 
			file, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	setup_redirections(t_token *redirections)
{
	t_token *curr;
	int		status;

	curr = redirections;
	while (curr)
	{
		if (curr->type == T_IN)
			status = input_redirection(curr->value);
		else if (curr->type == T_OUT)
			status = output_redirection(curr->value, false);
		else if (curr->type == T_APPEND)
			status = output_redirection(curr->value, true);
		if (status != EXIT_SUCCESS)
			return (status);
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}