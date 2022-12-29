/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:38:37 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/22 16:44:29 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return ;
	}
	new_pwd(d);
}

int	ft_cd(t_cmd *c, t_data *d)
{
	if (!c->full_cmd[1] || c->full_cmd[1][0] == '~')
	{
		cd_root(c, d);
		return (0);
	}
	else if (c->full_cmd[2])
		return(error(TOOARGS, 1, "cd", NULL));
	if (chdir(c->full_cmd[1]))
		return (error(PERROR, 1, "cd: ", c->full_cmd[1]));
	new_pwd(d);
	return (0);
}