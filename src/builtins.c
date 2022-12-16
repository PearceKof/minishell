/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:56:06 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/16 14:59:06 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern int g_status;

char	*search_env_var(char *var)
{
	char	*env_var;
	char	*tmp;
	size_t	i;

	i = 0;
	while (var[i] && var[i] != ' ')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != ' ')
	{
		tmp[i] = var[i];
		i++;
	}
	tmp[i] = '\0';
	env_var = getenv(tmp);
	free(tmp);
	return (env_var);
}	
/*
reproduit la commande echo
*/
static void	ft_echo(char **full_cmd)
{
	size_t	i;
	size_t	j;
	int		flag;

	i = 1;
	flag = 0;
	if (full_cmd[1][0] == '-' && full_cmd[1][1] == 'n' && !full_cmd[1][2])
	{
		flag = 1;
		i = 2;
	}
	if (full_cmd[1][0] == '$' && full_cmd[1][1] == '?')
	{
		printf("%d\n", g_status);
		flag = 1;
	}
	else
	{
		while (full_cmd[i])
		{
			j = 0;
			while (full_cmd[i][j])
			{
				write(1, &full_cmd[i][j], 1);
				j++;
			}
			if (full_cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	
	if (!flag)
		write(1, "\n", 1);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
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

int ft_cd(t_cmd *c, t_data *d)
{
	if (!c->full_cmd[1] || c->full_cmd[1][0] == '~')
	{
		cd_root(c, d);
		return (0);
	}
	else if (c->full_cmd[2])
		return(error(TOOARGS, 1, "cd", NULL));
	if (!chdir(c->full_cmd[1]))
		return (error(PERROR, 1, "cd: ", c->full_cmd[1]));
	new_pwd(d);
	return (0);
}

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

static int	ft_pwd(void)
{
	char	str[PATH_MAX];

	if ((getcwd(str, sizeof(str)) != NULL))
		printf("%s\n", str);
	return (0);
}
/*
check le premier mot de la commande, si il correspond à un builin, il va l'éxecuter
et return 1
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
	else if (ft_strnstr(cmd->full_cmd[0], "export", size) && size == 6 && !cmd->full_cmd[1])
		return (ft_env(d->env));
	else if (ft_strnstr(cmd->full_cmd[0], "pwd", size) && size == 3)
	{
		ft_pwd();
		return (1);
	}
	else if (ft_strnstr(cmd->full_cmd[0], "unset", size) && size == 5)
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "env", size) && size == 3)
		return (ft_env(d->env));
	return (0);
}