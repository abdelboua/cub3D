/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:46:30 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/17 23:12:35 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	
	la fonction strrchr est utilisée pour trouver 
	le dernier caractère d'une chaîne et renvoie 
	un pointeur sur ce caractère et renvoie NULL si pas trouvé
*/
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last_occurrence;

	if (!s)
		return (0);
	i = 0;
	last_occurrence = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			last_occurrence = (char *)&s[i];
		}
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (last_occurrence);
}
