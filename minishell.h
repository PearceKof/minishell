/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:29:47 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/21 19:08:18 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../my_lib/includes/libft.h"
# include "../my_lib/includes/gnl.h"
# include "../my_lib/includes/ft_printf.h"
# include "../my_lib/includes/ft_fprintf.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
typedef struct s_term
{
	char	**env;
}	t_term;

int		env_size(char **env);
t_term *init_term(char **envp);
char	*get_input(void);
void	execute_cmd(char **env, char *cmd);
int	execute(char **env, char *cmd);
#endif