/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:56:06 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/29 18:58:26 by blaurent         ###   ########.fr       */
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

static void	ft_echo(char **full_cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (full_cmd[++i])
	{
		j = 0;
		if (full_cmd[i][j] == '$' && full_cmd[i][j + 1] == '?')
		{
			ft_putnbr_fd(g_status, 1);
			i += 2;
		}
		else
			while (full_cmd[i][j])
				write(1, &full_cmd[i][j++], 1);
		if (full_cmd[i + 1])
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

int	exec_builtin(t_cmd *cmd)
{
	if (ft_strnstr("echo", cmd->full_cmd[0], ft_strlen(cmd->full_cmd[0])))
	{
		ft_echo(cmd->full_cmd);
		return (1);
	}
	else if (ft_strnstr(cmd->full_cmd[0], "cd", ft_strlen(cmd->full_cmd[0])))
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "pwd", ft_strlen(cmd->full_cmd[0])))
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "export", ft_strlen(cmd->full_cmd[0])))
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "unset", ft_strlen(cmd->full_cmd[0])))
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "env", ft_strlen(cmd->full_cmd[0])))
		return (1);
	else if (ft_strnstr(cmd->full_cmd[0], "exit", ft_strlen(cmd->full_cmd[0])))
		return (1);
	return (0);
}