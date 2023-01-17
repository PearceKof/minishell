/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:48:00 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/17 12:52:06 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_envvar(char *varname, char *value)
{
	char	*new_var;
	char	*tmp;

	tmp = ft_strjoin(varname, "=");
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
		malloc_error();
	i = 0;
	while (d->env[i])
	{
		new_env[i] = ft_strdup(d->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(addvar);
	new_env[i + 1] = NULL;
	ft_freetab(d->env);
	d->env = new_env;
}

char	*edit_envvar(char *to_edit, char *value, int size)
{
	char	*newvar;
	char	*tmp;

	tmp = ft_substr(to_edit, 0, size + 1);
	if (!tmp)
		malloc_error();
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
	char	*str;
	int		i;

	str = ft_getenv(varname, d->env, size);
	if (!str)
	{
		newvar = new_envvar(varname, value);
		addvar_to_env(d, newvar);
		free(newvar);
		free(str);
	}
	i = 0;
	while (d->env[i])
	{
		if (ft_strnstr(d->env[i], varname, ft_strlen(varname)))
			if (varname_size(d->env[i]) == size)
				d->env[i] = edit_envvar(d->env[i], value, size);
		i++;
	}
	free(str);
	return (d->env);
}
