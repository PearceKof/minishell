/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:56:06 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/17 13:31:30 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	export_err(char **env)
{
	int		i;
	char	*str;
	char	*ptr;

	i = 0;
	while (env && env[i])
	{
		str = isolate_varname(env[i], -1);
		ptr = ft_getenv(str, env, ft_strlen(str));
		printf("declare -x %s=\"%s\"\n", str, ptr);
		free(str);
		free(ptr);
		i++;
	}
	exit(0);
}

int	is_builtin(t_cmd *cmd)
{
	int	size;

	size = ft_strlen(cmd->full_cmd[0]);
	if (ft_strnstr("echo", cmd->full_cmd[0], size) && size == 4)
		return (1);
	else if (ft_strnstr("cd", cmd->full_cmd[0], size) && size == 2)
		return (1);
	else if (ft_strnstr("pwd", cmd->full_cmd[0], size) && size == 3)
		return (1);
	else if (ft_strnstr("export", cmd->full_cmd[0], size) && size == 6)
		return (1);
	else if (ft_strnstr("unset", cmd->full_cmd[0], size) && size == 5)
		return (1);
	else if (ft_strnstr("env", cmd->full_cmd[0], size) && size == 3)
		return (1);
	else if (ft_strnstr("exit", cmd->full_cmd[0], size) && size == 4)
		return (1);
	return (0);
}

int	exe_parent_builtin(t_cmd *c, t_data *d)
{
	int		size;

	if (c->full_cmd[0] == NULL || c->next != NULL)
		return (0);
	size = ft_strlen(c->full_cmd[0]);
	if (ft_strnstr("exit", c->full_cmd[0], size) && size == 4)
	{
		ft_exit(c->full_cmd, c, d);
		return (1);
	}
	else if (ft_strnstr("cd", c->full_cmd[0], size) && size == 2)
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

void	exe_child_builtin(t_cmd *c, t_data *d)
{
	int	size;

	size = ft_strlen(c->full_cmd[0]);
	if (ft_strnstr("echo", c->full_cmd[0], size) && size == 4)
		ft_echo(c->full_cmd);
	else if (ft_strnstr(c->full_cmd[0], "cd", size) && size == 2)
		cd_error(c, d);
	else if (ft_strnstr(c->full_cmd[0], "export", size)
		&& size == 6 && !c->full_cmd[1])
		export_err(d->env);
	else if (ft_strnstr(c->full_cmd[0], "pwd", size) && size == 3)
		ft_pwd();
	else if (ft_strnstr(c->full_cmd[0], "env", size) && size == 3)
		ft_env(d->env);
	exit(0);
}
