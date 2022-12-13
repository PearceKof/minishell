/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:29:47 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/13 16:18:09 by blaurent         ###   ########.fr       */
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

enum
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
	builtins.c
*/
int		exec_builtin(t_cmd *cmd, t_data *d);
/*
	dup_cmd.c
*/
char	*dup_cmd(const char *src);
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
	execute.c
*/
void	execute_cmd(char **env, char **cmd);
int	execute(t_cmd *c, t_data *d);
/*
	free.c
*/
void	*free_cmd(t_cmd *c);
/*
	init_cmd.c
*/
t_cmd	*init_cmd(char *input);
/*
	init.c
*/
t_data *init_term(char **av, char **envp);
int		redirection(char **input, t_cmd *c, size_t i, size_t j);
void	*ft_mallerror(char **tab, size_t i);
char	**split_cmd(char const *s);
char	*get_input(void);
t_cmd	*new_cmd();
t_cmd	*add_cmd(t_cmd *first);
t_cmd	*fill_cmd(char **input, t_cmd *first);
int		env_size(char **env);
int	error(int errorid, int error_status, char *infoa, char *infob);

#endif