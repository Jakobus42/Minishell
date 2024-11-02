/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:59:50 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:30:31 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_list_size(t_list **lst)
{
	t_list	*cur;
	int		i;

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
