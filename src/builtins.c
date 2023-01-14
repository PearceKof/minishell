/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:56:06 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/14 16:18:35 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static int	export_err(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		ft_printf("declare -x %s\n", env[i]);
		i++;
	}
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	int	size;

	size = ft_strlen(cmd->full_cmd[0]);
	if (ft_strnstr("echo", cmd->full_cmd[0], size) && size == 4)
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "cd", size) && size == 2)
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "pwd", size) && size == 3)
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "export", size) && size == 6)
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "unset", size) && size == 5)
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "env", size) && size == 3)
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "exit", size) && size == 4)
		return (1);
	return (0);
}

int	exe_parent_builtin(t_cmd *c, t_data *d)
{
	int		size;

	if (c->full_cmd[0] == NULL || c->next != NULL)
		return (0);
	size = ft_strlen(c->full_cmd[0]);
	if (ft_strnstr(c->full_cmd[0], "exit", size) && size == 4)
	{
		ft_exit(c->full_cmd, c, d);
		return (1);
	}
	else if (ft_strnstr(c->full_cmd[0], "cd", size) && size == 2)
			return (ft_cd(c, d));
	else if (ft_strnstr(c->full_cmd[0], "export", size)
		&& size == 6 && c->full_cmd[1])
		return (ft_export(c, d));
	else if (ft_strnstr(c->full_cmd[0], "unset", size) && size == 5)
	{
		ft_unset(c, d);
		return (1);
	}
	return (0);
}
/*
check le premier mot de la commande, si il correspond à un builin, 
il va l'éxecuter et return 1
sinon, return 0
*/
int	exe_child_builtin(t_cmd *cmd, t_data *d)
{
	int	size;

	size = ft_strlen(cmd->full_cmd[0]);
	if (ft_strnstr("echo", cmd->full_cmd[0], size) && size == 4)
	{
		ft_echo(cmd->full_cmd);
		return (1);
	}
	else if (ft_strnstr(cmd->full_cmd[0], "export", size)
		&& size == 6 && !cmd->full_cmd[1])
		return (export_err(d->env));
	else if (ft_strnstr(cmd->full_cmd[0], "pwd", size) && size == 3)
		return (ft_pwd());
	else if (ft_strnstr(cmd->full_cmd[0], "env", size) && size == 3)
		return (ft_env(d->env));
	return (0);
}
