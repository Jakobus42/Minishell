/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:15:34 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/07 20:15:36 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
/*
#include <ctype.h>
#include <stdio.h>

int main(void)
{
	int c = 'a';
	int result;
	int test;	

	result = ft_tolower(c);
	printf("%c\n", result);

	test =  tolower(c);
	printf("%c", test);

	return(0);
}
*/
