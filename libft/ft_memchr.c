/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:45:26 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/15 15:17:36 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	utilsation de la fonction memchr pour chercher 
	un caractère dans une zone de mémoire
	renvoie un pointeur sur le 
	premier caractère trouvé ou NULL si pas trouvé
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	cc;

	str = (unsigned char *)s;
	cc = (unsigned char)c;
	while (n--)
	{
		if (*str == cc)
			return (str);
		str++;
	}
	return (NULL);
}
