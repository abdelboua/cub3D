/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:45:34 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/17 23:15:39 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	utilsation de la fonction memmove pour copier 
	une zone de mémoire et renvoie un pointeur sur la zone de 
	destination ,la fonction est utilis pour copier une zone de mémoire 
	si la zone de destination et la zone source se chevauchent
	la fonction memcpy ne fonctionne pas dans ce cas 
	et est plus sécurisée que memcpy car elle gère les
	surpositions de mémoire
*/
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dst || !src)
		return (0);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d > s && d < s + n)
	{
		while (n--)
		{
			d[n] = s[n];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
