/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:56:06 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/03 18:01:42 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

extern int	g_status;

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (1);
}

void	new_pwd(t_data *d)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_getenv("PWD", d->env, 3);
	new_pwd = getcwd(NULL, 0);
	set_env_var("OLDPWD", old_pwd, d, 6);
	set_env_var("PWD", new_pwd, d, 3);
	free(new_pwd);
}

static int	ft_pwd(void)
{
	char	str[PATH_MAX];

	if ((getcwd(str, sizeof(str)) != NULL))
		printf("%s\n", str);
	return (0);
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
		return (ft_env(d->env));
	else if (ft_strnstr(cmd->full_cmd[0], "pwd", size) && size == 3)
	{
		ft_pwd();
		return (1);
	}
	else if (ft_strnstr(cmd->full_cmd[0], "env", size) && size == 3)
		return (ft_env(d->env));
	return (0);
}
