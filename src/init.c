/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:29 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/17 16:31:46 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *init_term(char **av, char **envp)
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
	d->env = ft_tabdup(envp);
	d->env = init_env(av, d);
	if (!d->env)
	{
		free(d);
		return (NULL);
	}
	return (d);
}
