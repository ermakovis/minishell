#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# define EOF (-1)
# define MSH_BUFF_SIZE 1024

typedef	struct	s_msh
{
	char	*command;
	char	**env;
    char    **tokens;
}				t_msh;

int		process_env(char **env, t_msh **msh);
int		ft_getchar(void);
char	*parse_env(char *var, char **env);
void	cleanup(t_msh **msh, int exit_code, char *message);
void	*ft_notrealloc(void *old_ptr, int old_size, int new_size);
void	msh_env(t_msh *msh);
#endif
