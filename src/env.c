/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:48:00 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/09 16:39:39 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	prends un nom de variable et une valeur, alloue et return un char *
	composé de varname, suivi d'un = et de value
*/
char	*new_envvar(char *varname, char *value)
{
	char	*new_var;
	char	*tmp;

	tmp = ft_strjoin(varname, "=");
	if (!tmp)
		malloc_error();
	new_var = ft_strjoin(tmp, value);
	if (!new_var)
		malloc_error();
	free(tmp);
	return (new_var);
}
/*
	prends en arg un ptr sur d du minishell et la variable à ajouter dans env
	alloue un nouvel env et y ajoute la nouvelle variable
	!!! Ajoute addvar peut importe si il est déjà dans l'env
	à utiliser seulement pour une nouvelle variable !!!
*/

void	addvar_to_env(t_data *d, char *addvar)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((ft_tablen(d->env) + 2) * sizeof(char *));
	if (!new_env)
		return ;
	i = 0;
	while (d->env[i])
	{
		new_env[i] = ft_strdup(d->env[i]);
		if (!new_env[i])
			malloc_error();
		i++;
	}
	new_env[i] = ft_strdup(addvar);
	if (!new_env[i])
		malloc_error();
	new_env[i + 1] = NULL;
	ft_freetab(d->env);
	d->env = new_env;
}
/*
	prends un ptr sur la variable à changer, 
	la nouvelle valeur et la taille de la variable
	return la variable suivi de sa nouvelle valeur
*/

char	*edit_envvar(char *to_edit, char *value, int size)
{
	char	*newvar;
	char	*tmp;

	tmp = ft_substr(to_edit, 0, size + 1);
	if (!tmp)
		malloc_error();
	newvar = ft_strjoin(tmp, value);
	if (!newvar)
		malloc_error();
	free(tmp);
	tmp = to_edit;
	to_edit = newvar;
	free(tmp);
	return (to_edit);
}
/*
	prends un nom de variable à créer ou éditer, la valeur qu'on veut
	lui donner, les data du shell, et la taille de varname
	si varname n'existe pas déjà dans l'env, créer la var,
	sinon il ne fait que changer la valeur
*/

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
	i = 0;
	while (d->env[i])
	{
		if (ft_strnstr(d->env[i], varname, ft_strlen(varname)))
			if (varname_size(d->env[i]) == size)
				d->env[i] = edit_envvar(d->env[i], value, size);
		i++;
	}
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
	if (!ft_getenv("PATH", d->env, 4))
		d->env = set_env_var("PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", d, 4);
	if (!ft_getenv("_", d->env, 1))
		d->env = set_env_var("_", av[0], d, 1);
	return (d->env);
}
