/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:07 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/07 18:38:32 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_mallerror(char **tab, size_t i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_error(char *where, char **freed, int ret)
{
	perror(where);
	if (freed)
		ft_freetab(freed);
	exit(ret);
}

void	*free_cmd(t_cmd *c)
{
	while (c)
	{
		ft_freetab(c->full_cmd);
		c->prev = NULL;
		c = c->next;
	}
	return (NULL);
}
