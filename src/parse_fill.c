/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:58:40 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/02 22:12:45 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	go_nxt_char(const char **s, int j, int size)
{
	char	del;

	*s += j;
	if (size == 0 && ((*s)[0] == '\'' || (*s)[0] == '\"'))
	{
		del = *s[0];
		*s += 1;
		while (*s[0] != del)
			*s += 1;
		*s += 1;
	}
	else if ((*s)[0] == '$')
	{
		*s += 1;
		while ((*s)[0] && !ft_strchr(SPE_CHAR, (*s)[0]))
			*s += 1;
	}
}

char	*fill_tab(char *tab, const char **s, char **env, int size)
{
	int		i;
	int		j;
	char	del;

	i = 0;
	j = 0;
	while (i < size && (*s)[j])
	{
		if ((*s)[j] == '\"' || (*s)[j] == '\'')
		{
			del = (*s)[j];
			j++;
			while ((*s)[j] && del != (*s)[j] && i < size)
			{
				if (del != '\'' && (*s)[j] == '$' && (*s)[j + 1] != '\0')
					tab = join_varvalue(s, &j, tab, &i, env);
				else
					tab = cpy_char(tab, &i, *s, &j);
			}
			j++;
		}
		else if ((*s)[j] == '$')
			tab = join_varvalue(s, &j, tab, &i, env);
		else
			tab = cpy_char(tab, &i, *s, &j);
	}
	tab[i] = '\0';
	go_nxt_char(s, j, size);
	return (tab);
}
