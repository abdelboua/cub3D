/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:46:14 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/14 23:27:06 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	la fonction strlcat est utilisée pour concaténer deux chaînes de caractères
	et renvoie la longueur totale de la chaîne résultante
	la fonction strlcat est utilisée pour éviter les débordements de mémoire
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	j = 0;
	while (src[j] != '\0' && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
