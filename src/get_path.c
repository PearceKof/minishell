/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:10:42 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/15 17:06:00 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char *relative_path(char **env, char *cmd)
{
	char	*tmp;
	char	*path;
	char	*pwd;

	pwd = ft_getenv("PWD", env, 3);
	tmp = ft_strjoin(pwd, "/");
	free(pwd);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

char	*checkpaths(char **env_paths, char *cmd)
{
	char	*cmdpath;
	char	*tmp;
	size_t	i;

	i = 0;
	while (env_paths[i])
	{
		tmp = ft_strjoin(env_paths[i], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(cmdpath, X_OK))
		{
			ft_freetab(env_paths);
			return (cmdpath);
		}
		free(cmdpath);
		i++;
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
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)) && cmd[0] == '/')
	{
		ptr = ft_strdup(cmd);
		return (ptr);
	}
	else if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (relative_path(env, cmd));
	ptr = ft_getenv("PATH", env, 4);
	env_paths = ft_split(ptr, ':');
	free(ptr);
	return (checkpaths(env_paths, cmd));
}
