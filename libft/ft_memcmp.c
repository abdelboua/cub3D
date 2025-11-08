/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:45:29 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/17 23:08:27 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	utilsation de la fonction memcmp pour comparer deux zones de mémoire
	renvoie 0 si les deux zones sont égales, 1 si la première est plus grande
	-1 si la deuxième est plus grande
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (*str1 > *str2)
			return (1);
		else if (*str1 < *str2)
			return (-1);
		str1++;
		str2++;
		i++;
	}
	return (0);
}
