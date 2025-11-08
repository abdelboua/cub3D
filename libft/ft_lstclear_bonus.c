/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:52:32 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/15 16:33:28 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	verification de lst ne suffit pas faut verifier aussi *lst 
	pour le pointeur vers la liste pas que la fonction
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current;
		current = current->next;
		del(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}
