/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:55:59 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/10 18:15:54 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char	**ft_tabdup(char **tab)
{
	char	**tabdup;
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	tabdup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tabdup)
		return (NULL);
	tabdup[i] = NULL;
	i = 0;
	while (tab[i])
	{
		tabdup[i] = ft_strdup(tab[i]);
		if (!tabdup[i] && tab[i])
		{
			while (i--)
				free(tabdup[i]);
			free(tabdup);
			return (NULL);
		}
		i++;
	}
	return (tabdup);
}
