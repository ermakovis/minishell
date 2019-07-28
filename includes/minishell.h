/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:10:41 by tcase             #+#    #+#             */
/*   Updated: 2019/07/28 16:41:13 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <sys/ioctl.h>
# include <term.h>
# include <dirent.h>
# include <curses.h>
# include <limits.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

# define MSH_BUFF_SIZE 2048
# define MSH_CMD_BUFF 262144
# define LEFT	4479771
# define RIGHT	4414235
# define UP	4283163
# define DOWN	4348699
# define DELETE	2117294875
# define BSPACE 127
# define TAB	9

typedef struct winsize	t_wsize;
typedef struct termios	t_term;
typedef struct stat		t_stat;
typedef struct dirent	t_dir;

typedef struct			s_cmd
{
	char				*area;
	char				*start;
	char				*clear_line;
	char				*clear_rest;
	char				*cur_start;
	char				*up;
	char				*left;
	char				*right;
	char				*del;
	char				*insert_mode_on;
	char				*insert_mode_off;
}						t_cmd;

typedef struct			s_lch
{
	char				**tokens;
	char				**env;
}						t_lch;

typedef struct			s_rl
{
	int					status;
	char				*line;
	int					history;
	char				*history_orig;
	t_list				*tab_items;
	size_t				line_len;
	size_t				cur_pos;
}						t_rl;

typedef struct			s_var
{
	char				*name;
	char				*value;
}						t_var;

typedef struct			s_bin
{
	char				*name;
	void				(*func)(void);
}						t_bin;

typedef struct			s_msh
{
	t_rl				*rl;
	t_cmd				*cmd;
	t_lch				*lch;
	t_term				*original_state;
	t_list				*tok;
	t_list				*var;
	t_list				*env;
	t_list				*bin;
	t_list				*history;
}						t_msh;

t_msh					*g_msh;

/*
**  main.c
*/
void					set_terminal_canon(void);
void					set_terminal_raw(void);

/*
**  init.c
**  --init_msh(void);
**  --init_cmd(void);
*/
void					init(char **env);

/*
**  init_env.c
*/
void					init_env(char **env);
char					*find_var(t_list *list, char *var_name);

/*
**  init_bins.c
**  --add_bin
*/
int						cmp_bins(t_bin *bin, char *data_ref);
void					init_bins(void);
void					delete_builtins(void *content, size_t size);

/*
**  read_line.c
*/
int						read_line(void);
void					init_rl(void);
int						get_char(long *ch);

/*
**  rl_input_manipulation.c
*/
void					rl_print_char(char ch);
void					rl_move_cur(long ch);
void					rl_del_char(long ch);

/*
**  rl_history.c
**  --rl_calc_hight(char *line);
*/
void					rl_history(long ch);
void					rl_add_history(void);

/*
**  rl_history_replace.c
*/
void					rl_history_change(int position);

/*
**  rl_tab.c
**  --tl_tab_compare
*/
void					rl_tab(long ch);

/*
**  parser.c
**  --add_token
*/
void					parse_line(void);

/*
**  pr_expans.c
*/
void					pr_expans_dsign(char **token, int *i, char **line);
void					pr_expans_tild(char **token, int *i, char **line);
void					pr_expans(char **token, int *i, char **line);

/*
**  pr_quotes.c
*/
void					pr_quotes(char **token, int *i, char **line);

/*
**  launch_programm.c
**  --find_exec_join
**  --check_bins
**  --get_full_path
**  --check_full_path
*/
void					launch_program(void);

/*
**  lch_checks.c
*/
void					lch_tokens(void);
void					lch_env(void);
void					lch_check_var(void);
int						lch_check_bins(void);

/*
**  find_executable.c
*/
void					find_executable(void);

/*
**  msh_small_funcs.c
*/
void					msh_env(void);
void					msh_exit(void);
void					msh_unsetenv(void);
void					msh_setenv(void);
void					msh_echo(void);

/*
**  msh_cd.c
**  --msh_cd_change
*/
void					msh_cd(void);

/*
**  utils.c
*/
void					realloc_check(char **old_ptr, size_t old_size);
void					ft_notrealloc(char **old_ptr, size_t old_size,\
							size_t new_size);
void					display_prompt(void);
void					append_str(char **str, int *i, char *new);
char					*var_to_str(t_var *var);

/*
**	ut_str_functions.c
*/
void					printl_str(t_list *list);
void					delete_str(void *content, size_t size);

/*
**  var_functions.c
*/
int						cmp_var(t_var *var, char *data_ref);
void					print_var(t_list *list);
void					set_var(t_list *list, char *var_name, char *var_value);
void					add_var(char *name, char *value, t_list **alist);
void					delete_var(void *content, size_t size);

/*
**  cleanup.c
*/
void					cleanup(int exit_code, char *message);
void					cl_rl_struct(void);
void					cl_lch_struct(void);
#endif
