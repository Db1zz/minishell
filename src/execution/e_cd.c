/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:16:38 by jroseiro          #+#    #+#             */
/*   Updated: 2024/10/24 17:59:44 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



void	e_cd(char * command)
{
	if (chdir(command) != 0)
		perror("chdir failed");
	if (!ft_strncmp(command, "~"))
}

// read man on chdir better