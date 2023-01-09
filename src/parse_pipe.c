/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:56:03 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/09 16:47:18 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipe(const char *s)
{
	char	del;
	int		i;
	int		count;

	i = 0;
	count = 0;
	del = '|';
	while (s[i])
	{
		if (s[i] == '|' && del == '|')
			i++;
		if (s[i] != '\0')
			count++;
		del = '|';
		while (s[i] != del && s[i] != '\0')
			del = nxt_del(s, del, '|', &i);
	}
	if (del != '|')
		return (-1);
	return (count);
}

static char	*fill_btw_pipe(char *tab, const char **s, int size)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < size && (*s)[j])
		tab = cpy_char(tab, &i, *s, &j);
	tab[i] = '\0';
	*s += j;
	if (*s[0] == '|')
		*s += 1;
	return (tab);
}

static char	*malloc_btw_pipe(const char **s, int size)
{
	char	*tab;

	tab = NULL;
	tab = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!tab)
		malloc_error();
	return (fill_btw_pipe(tab, s, size));
}

static int	size_btw_pipe(const char *s, char del)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i] && s[i] != del)
	{
		if (del == s[i] && (s[i] == '\"' || s[i] == '\''))
			del = '|';
		else if (del == '|' && (s[i] == '\"' || s[i] == '\''))
			del = s[i];
		size++;
		i++;
		if (del != '|' && s[i] == del)
		{
			del = '|';
			i++;
			size++;
		}
	}
	return (size);
}

char	**parse_pipe(const char *s)
{
	char	**tab;
	int		i;
	int		nb_of_pipe;

	// ft_fprintf(2, "parse_pipe begin\n");
	nb_of_pipe = count_pipe(s);
	// ft_fprintf(2, "parse_pipe nb of pipe: %d\n", nb_of_pipe);
	if (nb_of_pipe == -1)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (nb_of_pipe + 1));
	if (!tab)
		malloc_error();
	i = 0;
	while (i < nb_of_pipe)
	{
		// ft_fprintf(2, "parse_pipe loop %d\n", i);
		tab[i] = malloc_btw_pipe(&s, size_btw_pipe(s, '|'));
		if (!tab[i])
			return (free_tab_and_ret_null(tab, i));
		// ft_fprintf(2, "parse_pipe loop tab=|%s|\n", tab[i]);
		i++;
	}
	tab[i] = NULL;
	// ft_fprintf(2, "parse_pipe end\n");
	return (tab);
}
