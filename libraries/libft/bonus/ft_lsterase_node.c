#include "../libft.h"

t_list* ft_lsterase_node(t_list **lst, t_list *node_to_remove, void (*del)(void*)) {
    t_list *current = *lst;
    t_list *previous = NULL;

    if (!lst || !*lst || !node_to_remove || !del) {
        return NULL;
    }
    while (current) 
    {
        if (current == node_to_remove) 
        {
            if (previous == NULL)
                *lst = current->next;
            else
                previous->next = current->next;
            del(current->content);
            free(current);
            return previous ? previous : *lst;
        }
        previous = current;
        current = current->next;
    }
    return NULL;
}
