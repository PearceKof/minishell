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

char	*dup_cmd(const char *src)
{
	char	*mem;
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (src[i] != '\0')
		if (src[i++] != ' ')
			size++;
	if (size == 0)
		return (NULL);
	mem = malloc((size + 1) * sizeof(char));
	if (!mem)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		mem[i] = src[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

char	**dup_fullcmd(char **tab)
{
	char	**tabdup;
	int		i;

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
			exit(EXIT_FAILURE);
		i++;
	}
	return (tabdup);
}