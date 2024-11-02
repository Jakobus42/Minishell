#include "../libft.h"

bool	ft_lstnew_add_back(t_list **lst, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (1);
	ft_lstadd_back(lst, new);
	return (0);
}
