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

static char	**error_dup(char **freed, size_t size)
{
	while (--size)
		free(freed[size]);
	free(freed);
	return (NULL);
}

char	**dup_fullcmd(char **tab)
{
	char	**tabdup;
	int		i;
	size_t	size;

	i = -1;
	size = 0;
	while (tab[++i])
		if (!ft_strchr(tab[i], ' '))
			size++;
	tabdup = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tabdup)
		return (NULL);
	tabdup[size] = NULL;
	i = -1;
	size = 0;
	while (tab[++i])
	{
		if (!is_only_space(tab[i]))
			tabdup[size++] = dup_cmd(tab[i]);
		if (!tabdup[size - 1] && tab[i])
			return (error_dup(tabdup, size));
	}
	return (tabdup);
}