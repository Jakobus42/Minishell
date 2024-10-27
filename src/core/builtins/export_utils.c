#include "core/builtins/builtins.h"

static int	ft_strcmp_lilly(const char *s1, const char *s2)
{
	int	x;
	int	len_s1;
	int	len_s2;

	x = 0;
	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	while (s1[x] && s2[x] && s1[x] == s2[x])
		x++;
	if (x == len_s1 && len_s1 == len_s2)
		return (0);
	else
		return (s2[x] - s1[x]);
}

static void	swap(t_list **list)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;

	a = *list;
	b = (*list)->next;
	if (!a || !b)
		return ;
	c = b->next;
	a->next = c;
	b->next = a;
	*list = b;
	b->next = a;
	a->next = c;
}

void	sort_export(t_list **export)
{
	t_list	*exp;
	t_pair	*a;
	t_pair	*b;
	bool	swapped;

	swapped = true;
	while (swapped)
	{
		exp = *export;
		swapped = false;
		while (exp && exp->next)
		{
			a = exp->content;
			b = exp->next->content;
			if (ft_strcmp_lilly(a->key, b->key) < 0)
			{
				swap(&exp);
				swapped = true;
			}
			exp = exp->next;
		}
	}
}
