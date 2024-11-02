/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:46:02 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:46:03 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "core/expander/expander.h"
# include "libft/libft.h"

typedef struct s_shell	t_shell;

void					expand_tokens(t_shell *shell, t_list **tokens);

char					*expand_token(t_shell *shell, const char *token,
							const bool remove_quotes);

#endif // EXPANDER_H