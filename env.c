/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:22:27 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/21 16:20:41 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

t_term *init_term(char **envp)
{
	size_t	i;
	t_term	*ret;

	ret = malloc(sizeof(t_term));
	if (!ret)
	{
		printf("malloc failled\n");
		exit(EXIT_FAILURE);
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
			printf("malloc failled\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (ret);
}
