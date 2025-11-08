/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:45:31 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/14 23:58:04 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	utilsation de la fonction memcpy pour copier une zone de mémoire
	renvoie un pointeur sur la zone de destination
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;	

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dst);
}
