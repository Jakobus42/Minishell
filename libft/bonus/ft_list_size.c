/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:59:50 by jsadjina          #+#    #+#             */
/*   Updated: 2023/11/27 18:52:41 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h" 

int	ft_list_size(t_list **lst)
{
	t_list	*cur;
	int				i;

	i = 0;
	cur = (*lst);
	while ((*lst) != NULL)
	{
		i++;
		(*lst) = (*lst)->next;
	}
	(*lst) = cur;
	return (i);
}
