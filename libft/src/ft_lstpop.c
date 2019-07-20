#include <stdlib.h>
#include "libft.h"

void	ft_lstpop(t_list **alst, void (*del)(void*, size_t))
{
    t_list *tmp;

    if (!alst || !*alst)
	return ;
    tmp = (*alst)->next;
    del((*alst)->content, ((*alst)->content_size));
    free(*alst);
    *alst = tmp;
}
