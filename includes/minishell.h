#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

//# define EOF -1
# define MSH_BUFF_SIZE 2048

typedef struct		stat t_stat;
typedef struct	    s_bin t_bin;
typedef struct	    s_msh t_msh;

typedef struct		s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct	    s_bin
{
	char			*name;
	void			(*func)(t_msh*);
	struct s_bin    *next;
}					t_bin;

typedef struct		s_tok
{
	char			*token;
	struct s_tok	*next;	
}					t_tok;

typedef	struct	    s_msh
{
	char			**env;
	char			**tokens;
	t_bin			*bin;
	t_tok			*tok;
	t_var			*var;
}					t_msh;

int				add_token(char **str, int *i, t_msh *msh);
void			pop_token(t_msh *msh);
void			check_var(t_msh *msh);

void		    display_prompt(t_msh *msh);
void		    launch_program(t_msh *msh);
void			find_executable(t_msh *msh);
void		    process_builtins(t_msh *msh);
void		    process_env(char **env, t_msh **msh);
int				process_tokens(t_msh *msh);
void			process_tokens_quotes(char **str, int *i, int ch, t_msh *msh);
void			process_tokens_expans(char **str, int *i, int *ch, t_msh *msh);
void			process_tokens_expans_dsign(char **str, int *i, int *ch, t_msh *msh);
int				ft_getchar(void);
int				ft_tablesize(char **table);
char		    *parse_env(char *var, char **env);
void		    cleanup(t_msh **msh, int exit_code, char *message);
void		    clean_table(char ***table);
void		    clean_tokens(t_tok **tok);
void			realloc_check(char **str, int old_size, t_msh *msh);
char		    *ft_notrealloc(char *old_ptr, int old_size, int new_size);
void		    msh_env(t_msh *msh);
void		    msh_setenv(t_msh *msh);
void		    msh_unsetenv(t_msh *msh);
void		    msh_exit(t_msh *msh);
#endif
