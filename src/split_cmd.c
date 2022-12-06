/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:55:06 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/06 15:15:42 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_bracket(char const *s, char del, size_t *i)
{
	if (del == s[*i] && (s[*i] == '\"' || s[*i] == '\''))
		del = ' ';
	else if (del == ' ' && (s[*i] == '\"' || s[*i] == '\''))
		del = s[*i];
	*i += 1;
	if (del != ' ' && s[*i] == del)
	{
		del = ' ';
		*i += 1;
	}
	return (del);
}

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
			del = check_bracket(s, del, &i);
	}
	if (del != ' ')
		return (-1);
	return (count);
}

static const char	*dupstr_without_del(char **tab, const char *s, size_t i)
{
	char	del;
	size_t	j;
	size_t	k;

	*tab = (char *)malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
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
	return (dupstr_without_del(tab, s, i));
}

char	**split_cmd(char const *s)
{
	char	**tab;
	int		nbrofc;
	int		i;

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