/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:42:07 by jsadjina          #+#    #+#             */
/*   Updated: 2024/01/16 21:47:56 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_array_size(char **array)
{
    int i;

    i = 0;
    while(array && array[i])
        i++;
    return(i);
}
