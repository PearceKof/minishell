/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:53:18 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/19 13:53:18 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_cmd(t_cmd *c)
{
	t_cmd	*next;

	next = NULL;
	if (c)
	{
		next = c->next;
		ft_freetab(c->full_cmd);
		if (c->path)
			free(c->path);
		free(c);
		free_cmd(next);
	}
	return (NULL);
}

void	*free_env(t_data *d)
{
	int	i;

	i = 0;
	while (d->env[i])
	{
		free(d->env[i]);
		i++;
	}
	free(d->env);
	free(d->input);
	return (NULL);
}
