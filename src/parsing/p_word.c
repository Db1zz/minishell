/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_word.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:23:02 by gonische          #+#    #+#             */
/*   Updated: 2024/09/19 12:31:24 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*combine_words(t_list *words)
{
	char	*word;
	char	*temp;
	if (!words)
		return (NULL);
	word = ft_calloc(1, 1);
	if (!word)
		ft_printf("Calloc failed\n"); // TODO
	while (words)
	{
		temp = word;
		word = ft_strjoin(word, (char *)words->content);
		words = words->next;
		if (temp)
			free(temp);
	}
	return (word);
}
