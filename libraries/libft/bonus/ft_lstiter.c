/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:09:43 by jsadjina          #+#    #+#             */
/*   Updated: 2023/11/27 19:13:33 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_lstiter(t_list *lst, void (*f)(void *))
{
    if(!lst || !f)
        return ;
    while(lst)
    {
        f(lst->content);
        lst = lst->next;
    }
}