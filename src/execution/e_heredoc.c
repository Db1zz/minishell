/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:32:47 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/12 17:54:58 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "e_execute.h"

int	heredoc_redirection(const char *delimiter)
{
	const char	*filename = "/tmp/.heredoc";
	int			fd;
	char		*line;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("minishell: heredoc"), -1);
	while (true)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_dprintf(fd, "%s\n", line);
		free(line);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("minishell: heredoc"), unlink(filename), -1);
	if (dup2(fd, STDIN_FILENO) >= 0)
		return (close(fd), unlink(filename), 0);
	return (perror("minishell: heredoc dup2"), close(fd), unlink(filename), -1);
}
