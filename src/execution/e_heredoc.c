/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:32:47 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/11 19:57:01 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_execute.h"

// static void generate_tmp_filename(char *buffer, int size)
// {
// 	int	pid;
// 	pid = getpid();
// 	if 
// }

// int	heredoc_redirection(const char *delimeter)
// {
// 	char 	*filename = "/tmp/.heredoc";
// 	int fd;


// }

int heredoc_redirection(const char *delimiter)
{
    const char *filename = "/tmp/.heredoc";
    int fd;
    char *line;

    // Open file for writing heredoc content
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("minishell: heredoc");
        return -1;
    }

    // Read input until the delimiter is encountered
    while (1) {
        line = readline("> ");
        if (!line || strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);

    // Open file for reading and redirect STDIN
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("minishell: heredoc");
        unlink(filename);
        return -1;
    }

    if (dup2(fd, STDIN_FILENO) < 0) {
        perror("minishell: heredoc dup2");
        close(fd);
        unlink(filename);
        return -1;
    }

    close(fd);
    unlink(filename); // Cleanup the temporary file
    return 0;
}
