/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:36:07 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:43:36 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
/*
#include <ctype.h>
#include <stdio.h>

int main(void)
{
	int c = 'A';
	int result;
	int test;	

	result = ft_toupper(c);
	printf("%c\n", result);

	test =  toupper(c);
	printf("%c", test);

	return(0);
}
*/
