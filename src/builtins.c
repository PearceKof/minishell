/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:56:06 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/13 21:12:41 by blaurent         ###   ########.fr       */
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
/*
check le premier mot de la commande, si il correspond à un builin, 
il va l'éxecuter et return 1
sinon, return 0
*/
int	exec_builtin(t_cmd *cmd, t_data *d)
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
