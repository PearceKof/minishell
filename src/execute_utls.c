/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:10:42 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/08 18:57:57 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	execute_exit(t_cmd *c, t_data *d)
{
	int		size;

	size = ft_strlen(c->full_cmd[0]);
	if (ft_strnstr(c->full_cmd[0], "exit", size) && size == 4)
	{
		ft_exit(c->full_cmd, c, d);
		return (1);
	}
	else if (ft_strnstr(c->full_cmd[0], "cd", size) && size == 2)
	{
		if (c->next == NULL)
			ft_cd(c, d);
		return (2);
	}
	else if (ft_strnstr(c->full_cmd[0], "export", size)
		&& size == 6 && c->full_cmd[1])
	{
		ft_export(c, d);
		return (1);
	}
	else if (ft_strnstr(c->full_cmd[0], "unset", size) && size == 5)
	{
		ft_unset(c, d);
		return (1);
	}
	return (0);
}

char	*checkpaths(char **env_paths, char *cmd)
{
	char	*cmdpath;
	char	*tmp;
	size_t	i;

	i = 0;
	while (env_paths[i])
	{
		tmp = ft_strjoin(env_paths[i++], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(cmdpath, X_OK))
		{
			ft_freetab(env_paths);
			return (cmdpath);
		}
		free(cmdpath);
	}
	ft_freetab(env_paths);
	return (NULL);
}

char	*ft_getpaths(char **env, char *cmd)
{
	char	**env_paths;
	char	*ptr;

	if (*cmd == '\0')
		return (NULL);
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		if (access(cmd, X_OK))
			return (NULL);
		ptr = ft_strdup(cmd);
		return (ptr);
	}
	ptr = ft_getenv("PATH", env, 4);
	env_paths = ft_split(ptr, ':');
	free(ptr);
	return (checkpaths(env_paths, cmd));
}
