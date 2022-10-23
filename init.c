/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:29 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/23 16:49:55 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_env(char **envp)
{
	char ** new_env;
	size_t	i;

	new_env = (char **)malloc(sizeof(char *) * (env_size(envp) + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i] && envp[i])
		{
			while (i--)
				free(new_env[i]);
			free(new_env);
			ft_putstr_fd("malloc failled\n", 2);
			exit(1);
		}
		i++;
	}
	return (new_env);
}

t_data *init_term(char **envp)
{
	t_data	*d;

	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
	{
		ft_putstr_fd("malloc failled\n", 2);
		exit(1);
	}
	d->input = NULL;
	d->end = 0;
	d->env = dup_env(envp);
	if (!d->env)
		return (NULL);
	return (d);
}
