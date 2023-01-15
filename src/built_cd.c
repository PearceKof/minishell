/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:38:37 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/15 14:38:35 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	cd_root(t_cmd *c, t_data *d)
{
	char	*home;

	home = ft_getenv("HOME", d->env, 4);
	if (!home)
	{
		error(HNOSET, 1, "cd", NULL);
		return ;
	}
	if (chdir(home))
	{
		error(PERROR, 1, "cd: ", c->full_cmd[1]);
		free(home);
		return ;
	}
	free(home);
	new_pwd(d);
}

void	cd_error(t_cmd *c)
{
	if (!c->full_cmd[1])
		exit(0);
	if (c->full_cmd[2])
	{
		error(TOOARGS, 1, "cd", NULL);
		exit (1);
	}
	if (chdir(c->full_cmd[1]))
	{
		error(PERROR, 1, "cd: ", c->full_cmd[1]);
		exit (1);
	}
	exit (0);
}

int	ft_cd(t_cmd *c, t_data *d)
{
	if (!c->full_cmd[1] || c->full_cmd[1][0] == '~')
	{
		cd_root(c, d);
		return (1);
	}
	else if (c->full_cmd[2])
		return (0);
	if (chdir(c->full_cmd[1]))
		return (0);
	new_pwd(d);
	return (1);
}
