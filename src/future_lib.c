#include "minishell.h"

void	ft_lst_remove_if(t_list **alist, void *data_ref, int (*cmp)(), void (*del)())
{
    t_list	*last;
    t_list	*curr;
    t_list	*tmp;

    curr = *alist;
    while (curr)
    {
	if ((*cmp)(curr->content, data_ref) == 0)
	{  
	    if (curr == *alist)
	        *alist = curr->next;
	    else
		last->next = curr->next;
	    tmp = curr;
	    curr = curr->next;
	    del(tmp->content, tmp->content_size);
	    ft_memdel((void**)&tmp);
	}
	else
	{
	    last = curr;
	    curr = curr->next;
	}
    }
}

t_list	*ft_lst_find(t_list *alist, void *data_ref, int (*cmp)())
{
    while (alist)
    {
	if ((*cmp)(alist->content, data_ref) == 0)
	    return (alist);
	alist = alist->next;
    }
}

t_list	*ft_lst_num(t_list *alist, size_t num)
{
    size_t  i;

    i = 0;
    while (alist)
    {
	if (i++ == num)
	    return (alist);
	alist = alist->next;	
    }	

}

int	ft_test_path(char *path)
{
    t_stat	stat;
    int		ret;

    ret = 0;
    if (!path || !*path)
	return (-1);
    if (lstat(path, &stat) == -1)
	return (0);
    if (S_IRUSR & stat.st_mode)
	ret += 4;
    if (S_IWUSR & stat.st_mode)
	ret += 2;
    if (S_IXUSR & stat.st_mode)
	ret += 1;
    return (ret);
}

int	ft_item_type(char *path)
{
    t_stat	stat;

    if (!path || !*path)
	return (-1);
    if (lstat(path, &stat) == -1)
	return (0);
    if (S_ISSOCK(stat.st_mode))
	return (1);
    if (S_ISDIR(stat.st_mode))
	return (2);
    if (S_ISLNK(stat.st_mode))
	return (3);
    if (S_ISFIFO(stat.st_mode))
	return (4);
    if (S_ISCHR(stat.st_mode))
	return (5);
    if (S_ISBLK(stat.st_mode))
	return (6);
}

int	ft_table_size(char **table)
{
    int	    i;

    if (!table || !*table)
	return (-1);
    i = -1;
    while (table[++i]);
    return (i);
}

void	print_table(char **table)
{
    int	    i;

    if (!table && !table)
	return ;
    i = -1;
    while(table[++i])
	ft_printf("--%s\n", table[i]);
}
