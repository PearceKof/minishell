/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:29 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/01 17:35:56 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	d->env = ft_tabdup(envp);
	if (!d->env)
		return (NULL);
	return (d);
}
