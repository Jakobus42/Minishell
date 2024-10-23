/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:55:19 by jsadjina          #+#    #+#             */
/*   Updated: 2024/01/31 18:48:08 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strldup(int start, int limiter, char *str)
{
    char *tmp;
    int i;

    i = start;
    tmp = NULL;
    while(str[i] && str[i] != limiter)
        i++;
    tmp = ft_calloc(sizeof(char), i + 1);
    if(!tmp)
        return(NULL);
    i = 0;
    while(str[start] && str[start] != limiter)
    {
        tmp[i] = str[start];
        i++;
        start++;
    }
    return(tmp);
}