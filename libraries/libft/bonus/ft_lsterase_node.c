/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsterase_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:46:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:47:00 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lsterase_node(t_list **lst, t_list *node_to_remove,
		void (*del)(void *))
{
	t_list	*current;
	t_list	*previous;

	current = *lst;
	previous = NULL;
	if (!lst || !*lst || !node_to_remove || !del)
		return (NULL);
	while (current)
	{
		if (current == node_to_remove)
		{
			if (previous == NULL)
				*lst = current->next;
			else
				previous->next = current->next;
			del(current->content);
			free(current);
			if (previous)
				return (previous);
			return (*lst);
		}
		previous = current;
		current = current->next;
	}
	return (NULL);
}
