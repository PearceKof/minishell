/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:29 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/22 15:01:38 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_term *init_term(char **envp)
{
	size_t	i;
	t_term	*ret;

	ret = malloc(sizeof(t_term));
	if (!ret)
	{
		ft_putstr_fd("malloc failled\n", 2);
		exit(1);
	}
	i = 0;
	ret->env = malloc(sizeof(char *) * (env_size(envp) + 1));
	while (envp[i])
	{
		ret->env[i] = ft_strdup(envp[i]);
		if (!ret->env[i] && envp[i])
		{
			while (i--)
				free(ret->env[i]);
			free(ret);
			ft_putstr_fd("malloc failled\n", 2);
			exit(1);
		}
		i++;
	}
	return (ret);
}
