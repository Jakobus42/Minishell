/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:51:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:51:29 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/tokenizer/tokenizer.h"

const char	*token_type_to_str(const t_token_type type)
{
	if (type == WORD)
		return ("[WORD]");
	else if (type == PIPE)
		return ("[PIPE]");
	else if (type == REDIRECT_OUT)
		return ("[REDIRECT_OUT]");
	else if (type == REDIRECT_APPEND)
		return ("[REDIRECT_APPEND]");
	else if (type == REDIRECT_IN)
		return ("[REDIRECT_IN]");
	else if (type == HEREDOC)
		return ("[HEREDOC]");
	else
		return ("[NONE]");
}

bool	is_redirect(const t_token_type type)
{
	return (type == REDIRECT_APPEND || type == REDIRECT_OUT
		|| type == REDIRECT_IN || type == HEREDOC);
}
