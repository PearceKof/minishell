/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:58:40 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/29 14:29:31 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				if (del != '\'' && (*s)[j] == '$')
					tab = join_varvalue(s, &j, tab, &i, env);
				else
				{
					tab[i] = (*s)[j];
					i++;
					j++;
				}
			}
			j++;
		}
		else if ((*s)[j] == '$')
			tab = join_varvalue(s, &j, tab, &i, env);
		else
		{
			tab[i] = (*s)[j];
			i++;
			j++;
		}
	}
	tab[i] = '\0';
	*s += j;
	if (size == 0 && ((*s)[0] == '\'' || (*s)[0]  == '\"'))
	{
		del = *s[0];
		*s += 1;
		while (*s[0] != del)
			*s += 1;
		*s += 1;
	}
	else if (size == 0 && (*s)[0] == '$')
	{
		*s += 1;
		while ((*s)[0] && (*s)[0] != ' ' && (*s)[0] != '\'' && (*s)[0] != '\"' && (*s)[0] != '$')
			*s += 1;
	}
	return (tab);
}
