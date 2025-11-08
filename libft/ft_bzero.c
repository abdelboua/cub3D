/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:44:47 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/14 23:06:36 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*	
	utilsation de la fonction bzero pour initialiser une zone de mémoire à 0
	pour initialiser une structure ou un tableau, sa contiendra uniquement des 0
*/
void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
