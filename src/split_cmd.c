/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:55:06 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/07 17:39:01 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_space(char const *s)
{
	char	del;
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
			count++;
		del = ' ';
		while (s[i] && s[i] != del)
		{
			if (del == s[i] && (s[i] == '\"' || s[i] == '\''))
				del = ' ';
			else if (del == ' ' && (s[i] == '\"' || s[i] == '\''))
				del = s[i];
			else if (s[i] == '$' && del != '\'')
				count++;
			i++;
			if (del != ' ' && s[i] == del)
			{
				del = ' ';
				i++;
			}
		}
	}
	printf("count : %d del : |%c|\n", count, del);
	if (del != ' ')
		return (-1);
	return (count);
}

static void	*ft_mallerror(char **tab, size_t i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static const char	*dupstr_without_del(char **tab, const char *s, size_t i)
{
	char	del;
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (j < i)
	{
		if (s[j] == '\"' || s[j] == '\'')
		{
			del = s[j++];
			while (s[j] && del != s[j] && j < i)
				(*tab)[k++] = s[j++];
		}
		else
			(*tab)[k++] = s[j++];
	}
	(*tab)[j] = '\0';
	return (&s[j]);
}

static const char	*ft_fill_tab(char **tab, const char *s)
{
	char	del;
	size_t	i;

	while (*s && *s == ' ')
		s++;
	i = 0;
	del = ' ';
	if ((*s == '\"' || *s == '\''))
		del = s[i++];
	while (s[i] && s[i] != del)
	{
		if (del == s[i] && (s[i] == '\"' || s[i] == '\''))
			del = ' ';
		else if (del == ' ' && (s[i] == '\"' || s[i] == '\''))
			del = s[i];
		i++;
		if (del != ' ' && s[i] == del)
		{
			del = ' ';
			i++;
		}
	}
	*tab = (char *)malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	return (dupstr_without_del(tab, s, i));
}

char	**split_cmd(char const *s)
{
	char	**tab;
	int		nbrofc;
	size_t	i;

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