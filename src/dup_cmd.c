/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:21:28 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/28 17:21:28 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_fullcmd(char **tab)
{
	char	**tabdup;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	tabdup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tabdup)
		malloc_error();
	tabdup[i] = NULL;
	i = 0;
	while (tab[i])
	{
		tabdup[i] = ft_strdup(tab[i]);
		if (!tabdup[i] && tab[i])
			malloc_error();
		i++;
	}
	return (tabdup);
}
