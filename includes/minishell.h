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
    char    *env_cwd;
    char    **env_path;
    char    **tokens;
}		t_msh;

void		cleanup(t_msh **msh, int exit_code, char *message);
int		process_env(char **env, t_msh *msh);

#endif
