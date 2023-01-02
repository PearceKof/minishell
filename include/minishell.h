/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:29:47 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/02 20:29:48 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/gnl.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/ft_fprintf.h"
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>

# define SPE_CHAR " $\\|#=[]!><;{}()*?~&+-/\"'°"

enum	e_error
{
	PERROR,
	QUOTE,
	PIPEN,
	SUPERR,
	INFERR,
	DSUPERR,
	DINFERR,
	NL,
	NDIR,
	NPERM,
	PIPERR,
	FORKERR,
	NCMD,
	DUPERR,
	OPT,
	INVID,
	HNOSET,
	TOOARGS,
	NUMARGS
};

typedef struct s_data
{
	char	**env;
	char	*input;
	int		end;
	pid_t	pid;
}	t_data;

typedef struct s_cmd
{
	int					in;
	int					out;
	pid_t				pid;
	char				**full_cmd;
	char				*full_path;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;
/*
	builtins.c + built_*.c
*/
void	cd_root(t_cmd *c, t_data *d);
int		ft_cd(t_cmd *c, t_data *d);
void	ft_echo(char **full_cmd);
int		ft_exit(char **full_cmd);
int		ft_export(t_cmd *c, t_data *d);
int		ft_unset(t_cmd *c, t_data *d);
void	new_pwd(t_data *d);
int		ft_unset(t_cmd *c, t_data *d);
int		exec_builtin(t_cmd *cmd, t_data *d);
void	exit_test(void);
int		ft_env(char **env);
void	new_pwd(t_data *d);
/*
	dup_cmd.c
*/
char	*dup_cmd(char *src);
char	**dup_fullcmd(char **tab);
/*
	env.c
*/
int		varname_size(char *varname);
char	*ft_getenv(char *varname, char **env, int len);
char	*new_envvar(char *varname, char *value);
void	addvar_to_env(t_data *d, char *addvar);
char	*edit_envvar(char *to_edit, char *value, int size);
char	**set_env_var(char *varname, char *value, t_data *d, int size);
char	**init_env(char **av, t_data *d);
/*
	error.c
*/
int		error(int errorid, int error_status, char *infoa, char *infob);
void	malloc_error();
/*
	execute.c
*/
void	execute_cmd(char **env, char **cmd);
int		execute(t_cmd *c, t_data *d);
/*
	free.c
*/
void	*free_cmd(t_cmd *c);
/*
	init_cmd.c
*/
t_cmd	*init_cmd(char *input, char **env);
/*
	init.c
*/
t_data	*init_term(char **av, char **envp);
t_cmd 	*redirection(t_cmd *c, const char *s);
void	*ft_mallerror(char **tab, size_t i);
char	**split_cmd(char const *s, char **env);
char	*get_input(void);
t_cmd	*new_cmd();
t_cmd	*add_cmd(t_cmd *first);
t_cmd	*fill_cmd(char **input, t_cmd *first);
int		env_size(char **env);
/*
	parse_cmd.c
*/
char	nxt_del(char const *s, char del, char dfdel, int *i);
char	**parse_cmd(char const *s, char **env);
/*
	parse_fill.c
*/
char	*fill_tab(char *tab, const char **s, char **env, int size);
/*
	parse_pipe.c
*/
char	**parse_pipe(char const *s);
/*
	parse_redirection.c
*/

/*
	parse_size.c
*/
int		status_size(int *i);
int		var_value_size(char **env, const char *s, int *i);
int		get_str_size(const char *s, char **env, char del);
/*
	parse_utils.c
*/
void	pass_until_char(const char *s, int *i, char *ending_char);
char	*cpy_char(char *dest, int *i, const char *src, int *j);
void	*free_tab_and_ret_null(char **tab, int size);
/*
	parse_var.c
*/
char	*isolate_varname(const char *s, int start);
char	*join_varvalue(const char **s, int *j, char *tab, int *k, char **env);
/*
	signaux.c
*/
void	signaux();

int		is_only_space(char *s);

#endif