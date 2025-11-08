/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:46:03 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/16 04:17:50 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	utilsation de la fonction strchr pour chercher un caractère dans une chaîne
	renvoie un pointeur sur le premier caractère trouvé ou NULL si pas trouvé
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
