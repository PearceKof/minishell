/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:58:40 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/11 22:58:57 by blaurent         ###   ########.fr       */
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
	del = ' ';
	nxt = get_nxt(*s);
	while (i < size && (*s)[j])
	{
		if (del != new_delimiter(del, (*s)[j]))
		{
			del = new_delimiter(del, (*s)[j]);
			j++;
		}
		else if ((*s)[j] == '$' && del != '\'' && !ft_strchr(" ", (*s)[j + 1]))
			tab = join_varvalue(tab, &i, get_var_value(*s, &j, env));
		else
		{
			tab[i] = (*s)[j];
			i++;
			j++;
		}
	}
	*s += nxt;
	return (tab);
}
