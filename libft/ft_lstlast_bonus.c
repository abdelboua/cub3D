/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:43:54 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/15 16:46:34 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	Parcours de la liste : lst->next != NULL, 
	tant qu'il y a un nœud suivant, on continue de parcourir la liste. 
	Dès que lst->next devient NULL, 
	on sait qu'on est arrivé au dernier nœud.
*/
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
