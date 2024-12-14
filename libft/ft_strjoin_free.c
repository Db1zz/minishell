/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:47:29 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/14 14:59:24 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
 * ft_strjoin_free - Concatenates two strings and optionally frees the inputs.
 * @s1: First string.
 * @s2: Second string.
 * @free_flag: Determines which strings to free:
 *             - 0: Free neither string.
 *             - JOIN_FREE_S1: Free s1.
 *             - JOIN_FREE_S2: Free s2.
 *             - JOIN_FREE_BOTH: Free both s1 and s2.
 * 
 * Returns:
 * - Newly allocated string resulting from the concatenation.
 * - NULL if memory allocation fails.
 */

char *ft_strjoin_free(char *s1, char *s2, int free_flag)
{
	char	*result;
	size_t	len1; 
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	if (free_flag & JOIN_FREE_S1)
		free(s1);
	if (free_flag & JOIN_FREE_S2)
		free(s2);
	return (result);
}
