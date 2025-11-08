/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:46:33 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/15 16:35:18 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	 limiter ta recherche à une certaine portion(n 1er car) 
	 de la chaîne (ex : dans un buffer fixe).
	 elle ne modifie rien.
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	while (*big && len >= little_len)
	{
		if (ft_memcmp(big, little, little_len) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
