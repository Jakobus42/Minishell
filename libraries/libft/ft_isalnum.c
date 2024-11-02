/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:24:41 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:32:39 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int nc)
{
	if (((nc >= 'A' && nc <= 'Z') || (nc >= 'a' && nc <= 'z') || (nc >= '0'
				&& nc <= '9')))
		return (8);
	return (0);
}
