/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:48:00 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/17 16:15:01 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varname_size(char *varname)
{
	int	i;

	i = -1;
	while (varname[++i])
		if (varname[i] == '=')
			return (i);
	return (0);
}

char	*ft_getenv(char *varname, char **env, int len)
{
	int	lencmp;
	int	i;

	i = -1;
	while (env[++i])
	{
		lencmp = varname_size(env[i]);
		if (ft_strnstr(env[i], varname, ft_strlen(varname)) && lencmp == len)
			return (ft_strchr(env[i], '=') + 1);
	}
	return (NULL);
}

char	*new_envvar(char *varname, char *value)
{
	char	*new_var;
	char	*tmp;

	tmp =ft_strjoin(varname, "=");
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	return (new_var);
}

void	addvar_to_env(t_data *d, char *addvar)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((ft_tablen(d->env) + 2) * sizeof(char *));
	if (!new_env)
		return ;
	i = -1;
	while (d->env[++i])
	{
		new_env[i] = ft_strdup(d->env[i]);
		if (!new_env[i])
		{
			while (i--)
				free(new_env[i]);
			free(new_env);
			return ;
		}
	}
	new_env[i++] = ft_strdup(addvar);
	new_env[i] = NULL;
	ft_freetab(d->env);
	d->env = new_env;
}

char	*edit_envvar(char *to_edit, char *value, int size)
{
	char	*newvar;
	char	*tmp;

	tmp = ft_substr(to_edit, 0, size + 1);
	newvar = ft_strjoin(tmp, value);
	free(tmp);
	tmp = to_edit;
	to_edit = newvar;
	free(tmp);
	return (to_edit);
}

char	**set_env_var(char *varname, char *value, t_data *d, int size)
{
	char	*newvar;
	int		i;

	if (ft_getenv(varname, d->env, size) == NULL)
	{
		newvar = new_envvar(varname, value);
		addvar_to_env(d, newvar);
		free(newvar);
	}
	i = -1;
	while (d->env[++i])
		if (ft_strnstr(d->env[i], varname, ft_strlen(varname)))
			if (varname_size(d->env[i]) == size)
				d->env[i] = edit_envvar(d->env[i], value, size);
	return (d->env);
}

char	**init_env(char **av, t_data *d)
{
	char	*tmp;

	if (!d)
		return (NULL);
	tmp = getcwd(NULL, 0);
	d->env = set_env_var("PWD", tmp, d, 3);
	free(tmp);
	if (!ft_getenv("SHLVL", d->env, 5))
		d->env = set_env_var("SHLVL", "1", d, 5);
	if (!ft_getenv("PATH", d->env, 4))
		d->env = set_env_var("PATH", 
			"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", d, 4);
	if (!ft_getenv("_", d->env, 1))
		d->env = set_env_var("_", av[0], d, 1);
	return (d->env);
}
