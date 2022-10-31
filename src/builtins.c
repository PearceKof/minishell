/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:56:06 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/27 18:36:44 by blaurent         ###   ########.fr       */
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

void	ft_echo(char *cmd)
{
	char	*var;
	char	*tmp;
	int		bracket;
	size_t	i;

	i = 0;
	tmp = cmd + 4;
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			if (tmp[i + 1] == '?')
			{
				ft_putnbr_fd(g_status, 1);
				i += 2;
			}
			else
			{
				var = search_env_var(&tmp[i + 1]);
				if (var)
					write(1, var, ft_strlen(var));
				while (tmp[i] != ' ' && tmp[i] != '\0')
					i++;
			}
		}
		write(1, &tmp[i++], 1);
	}
	write(1, "\n", 1);
}

int	exec_builtin(char *cmd)
{
	if (ft_strnstr(cmd, "echo", 5))
	{
		ft_echo(cmd);
		return (1);
	}
	else if (ft_strnstr(cmd, "cd", ft_strlen(cmd)))
		return (1);
	else if (ft_strnstr(cmd, "pwd", ft_strlen(cmd)))
		return (1);
	else if (ft_strnstr(cmd, "export", ft_strlen(cmd)))
		return (1);
	else if (ft_strnstr(cmd, "unset", ft_strlen(cmd)))
		return (1);
	else if (ft_strnstr(cmd, "env", ft_strlen(cmd)))
		return (1);
	else if (ft_strnstr(cmd, "exit", ft_strlen(cmd)))
		return (1);
	return (0);
}