/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:45:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 16:04:31 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft/libft.h"
# include "utils/utils.h"

typedef struct s_pair
{
	char	*key;
	char	*value;
}			t_pair;

char		*get_env(t_shell *shell, t_list *env, const char *key);
bool		set_env(t_shell *shell, t_list *env, char *key, char *value);
bool		remove_env_pair(t_list *env, const char *key);
char		**convert_env_to_array(t_shell *shell, t_list *env);
t_list		*convert_env_to_list(t_shell *shell, const char **env);

/*ENV_UTILS*/
bool		lst_del_node(t_list *list, t_pair *pair);
void		free_pair(t_pair *pair);
t_pair		*create_pair(const char *str);
bool		valid_env(t_shell *shell, char *s);
void		print_env(t_list *env);

/*ENV_UTILS_TOO*/
int			vks(const char *key);
t_pair		*make_new_pair(t_pair *p, t_shell *s, char *k, char *v);

#endif // ENV_H