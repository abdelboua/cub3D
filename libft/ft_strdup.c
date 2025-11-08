/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:46:06 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/14 01:28:54 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s1);
	dup = (char *)malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s1, len);
	dup[len] = '\0';
	return (dup);
}
