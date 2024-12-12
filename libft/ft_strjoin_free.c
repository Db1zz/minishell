/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:47:29 by jroseiro          #+#    #+#             */
/*   Updated: 2024/12/12 14:09:33 by jroseiro         ###   ########.fr       */
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
 *             - 1: Free s1.
 *             - 2: Free s2.
 *             - 3: Free both s1 and s2.
 * 
 * Returns:
 * - Newly allocated string resulting from the concatenation.
 * - NULL if memory allocation fails.
 */

char *ft_strjoin_free(char *s1, const char *s2, int free_flag)
{
	char	*result;
	size_t	len1; 
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1); // +1 for /0
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	if (free_flag == 1 || free_flag == 3)
		free(s1);
	if (free_flag == 2 || free_flag == 3)
		free(s1);
	return (result);
}
