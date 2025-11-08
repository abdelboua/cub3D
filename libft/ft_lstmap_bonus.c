/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:13:13 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/16 04:36:16 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// on cree 3 variable : nouvelle liste qu’on va construire,  
// nouveau maillon, Le contenu transformé
// Appliquer f à l'ancien contenu pour le transformer 
// puis on créer un nouveau maillon avec ce nouveau contenu
// En cas d'échec d'allocation, nettoyer la nouvelle liste
// Ajouter le nouveau maillon à la fin de la nouvelle liste
// Passer au maillon suivant de la liste originale
// Retourner la tête de la nouvelle liste créée
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;

	if (!f || !del || !lst)
		return (NULL);
	new_list = NULL;
	tmp = NULL;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			while (new_list)
			{
				tmp = new_list->next;
				(*del)(new_list->content);
				free(new_list);
				new_list = tmp;
			}
			return (NULL);
		}
		ft_lstadd_back(&new_list, tmp);
		lst = lst->next;
	}
	return (new_list);
}
