#include "core/builtins/builtins.h"
#include "core/env/env.h"
#include "core/shell/shell.h"

int	get_valid_key_size(const char *key)
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
