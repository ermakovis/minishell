#include "minishell.h"

void realloc_check(char **old_ptr, size_t old_size)
{
    size_t  new_size;
    char    *new_str;

    if (!old_ptr || !*old_ptr || old_size % MSH_BUFF_SIZE != 0)
	return ;
    new_size = ((old_size / MSH_BUFF_SIZE) + 1) * MSH_BUFF_SIZE;
    ft_notrealloc(old_ptr, old_size, new_size);
}

void	ft_notrealloc(char **old_ptr, size_t old_size, size_t new_size)
{
    char    *new_ptr;

    if (!old_ptr || !*old_ptr)
	return ;
    if (!(new_ptr = ft_strnew(new_size)))
	cleanup(-1, "Failed to realloc");
    ft_memcpy(new_ptr, *old_ptr, old_size);
    ft_memdel((void**)old_ptr);
    *old_ptr = new_ptr;
}

void	append_str(char **str, int *i, char *new)
{
    int	    j;

    j = -1;
    while (new[++j])
    {
	realloc_check(str, *i + 1);
	(*str)[(*i)++] = new[j];
    }
}

void	display_prompt(void)
{
    char	*home;
    char	*pwd;
    int		home_len;

    if (!isatty(0))
	return ;
    home = find_var(g_msh->env, "HOME");
    pwd = find_var(g_msh->env, "PWD");
    home_len = ft_strlen(home);
    if (ft_strnequ(pwd, home, home_len))
    {
	ft_printf("~%s $: ", pwd + home_len);	
    }
    else
	ft_printf("%s $: ", pwd);
}
