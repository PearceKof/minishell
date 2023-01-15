/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:58:40 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/15 17:42:20 by blaurent         ###   ########.fr       */
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
		if (ft_strchr(" |&<>;", s[nxt]) && del == ' ')
			break ;
		nxt++;
	}
	return (nxt);
}

char	*join_home(char *tab, int *i, int *j, char **env)
{
	char	*home_value;
	int		k;

	*j += 1;
	home_value = get_home(env);
	if (!home_value)
	{
		tab[*i] = '~';
		*i += 1;
		return (tab);
	}
	k = 0;
	while (home_value[k])
		tab = cpy_char(tab, i, home_value, &k);
	free(home_value);
	return (tab);
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
		else if (del == ' ' && is_home_char((*s), j))
			tab = join_home(tab, &i, &j, env);
		else if ((*s)[j] == '$' && del != '\'' && !ft_strchr(" ", (*s)[j + 1]))
			tab = join_varvalue(tab, &i, get_var_value(*s, &j, env));
		else
			tab = cpy_char(tab, &i, *s, &j);
	}
	*s += nxt;
	return (tab);
}
