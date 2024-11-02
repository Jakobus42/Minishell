/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_too.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:50:20 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:50:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins/builtins.h"
#include "core/env/env.h"
#include "core/shell/shell.h"

int	vks(const char *key)
{
	const char	*start;

	start = key;
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	key++;
	while (*key && (ft_isalnum(*key) || *key == '_'))
		key++;
	return (key - start);
}

t_pair	*make_new_pair(t_pair *p, t_shell *s, char *k, char *v)
{
	p->key = ft_strdup(k);
	if (!p->key)
		error_fatal(s, "strdup in set_env failed\n", MALLOC_FAIL);
	p->value = ft_strdup(v);
	if (!p->value)
		error_fatal(s, "strdup in set_env failed\n", MALLOC_FAIL);
	return (p);
}
