/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:58:40 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/11 15:26:54 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nxt(const char *s)
{
	char	del;
	int		nxt;

	nxt = 0;
	del = ' ';
	while (s[nxt])
	{
		del = new_delimiter(del, s[nxt]);
		if (s[nxt] == ' ' && del == ' ')
			break;
		nxt++;
	}
	return (nxt);
}

char	*fill_tab(char *tab, const char **s, char **env, int size)
{
	int		i;
	int		j;
	int		nxt;
	char	del;

	i = 0;
	j = 0;
	nxt = get_nxt(*s);
	while (i < size && (*s)[j])
	{
		if ((*s)[j] == '\"' || (*s)[j] == '\'')
		{
			del = (*s)[j];
			j++;
			while ((*s)[j] && del != (*s)[j] && i < size)
			{
				if (del != '\'' && (*s)[j] == '$' && !ft_strchr(" \"\'", (*s)[j + 1]))
					tab = join_varvalue(s, &j, tab, &i, env);
				else
					tab = cpy_char(tab, &i, *s, &j);
			}
			j++;
		}
		else if ((*s)[j] == '$' && (*s)[j + 1] != '\0' && (*s)[j + 1] != ' ')
			tab = join_varvalue(s, &j, tab, &i, env);
		else
			tab = cpy_char(tab, &i, *s, &j);
	}
	tab[i] = '\0';
	*s += nxt;
	return (tab);
}
