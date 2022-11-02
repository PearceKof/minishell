/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:55:06 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/02 17:03:35 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_space(char const *s)
{
	size_t	i;
	int		count;
	char	bracket;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '\"' || s[i] == '\'')
		{
			bracket = s[i++];
			while (s[i++] != bracket)
				if (s[i] == '\0')
					return (-1);
			count++;
		}
		if (s[i] != '\0')
			count++;
		while (s[i] != ' ' && s[i] != '\0')
			i++;
	}
	return (count);
}

static void	*ft_mallerror(char **tab, size_t i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static const char	*ft_fill_tab(char **tab, const char *s)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	del;

	del = ' ';
	while (*s && *s == ' ')
		s++;
	if (*s && (*s == '\"' || *s == '\''))
		del = *s++;
	i = 0;
	while (s[i] && s[i] != del)
		i++;
	*tab = (char *)malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	j = 0;
	k = 0;
	while (j < i)
	{
		if (s[j] == '\"' || s[j] == '\'')
			j++;
		else
		{
			(*tab)[k] = s[j];
			j++;
			k++;
		}
	}
	(*tab)[j] = '\0';
	return (&s[j]);
}

char	**split_cmd(char const *s)
{
	char	**tab;
	size_t	i;
	int		nbrofc;

	if (!s)
		return (NULL);
	nbrofc = ft_count_space(s);
	if (nbrofc == -1)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (nbrofc + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < nbrofc)
	{
		s = ft_fill_tab(&tab[i], s);
		if (!tab[i])
			return (ft_mallerror(tab, i));
		i++;
	}
	tab[i] = NULL;
	return (tab);
}