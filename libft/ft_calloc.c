/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:44:57 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/14 23:08:22 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	utilsation de la fonction malloc pour allouer une zone de mémoire
	et initialiser cette zone à 0
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*copy;

	if (count == 0 || size == 0)
		return (malloc(0));
	if ((size != 0 && ((count * size) / size != count)) || (size >= 2147483647
			&& count >= 2147483647))
		return (NULL);
	copy = malloc(count * size);
	if (!copy)
		return (NULL);
	ft_memset(copy, 0, (count * size));
	return (copy);
}
