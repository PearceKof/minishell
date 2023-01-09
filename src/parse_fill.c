/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:58:40 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/09 23:29:12 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	go_nxt_char(const char **s, int j, int size)
// {
// 	char	del;

// 	ft_fprintf(2, "go_nxt_char1 s = |%s| j= %d\n", *s, j);
// 	*s += j;
// 	ft_fprintf(2, "go_nxt_char2 s = |%s|\n", *s);
// 	if (size == 0 && ((*s)[0] == '\'' || (*s)[0] == '\"'))
// 	{
// 		ft_fprintf(2, "go_nxt_char A\n");
// 		del = *s[0];
// 		*s += 1;
// 		while (*s[0] != del)
// 			*s += 1;
// 		*s += 1;
// 	}
// 	else if (((*s)[0] == '\'' || (*s)[0] == '\"') && (*s)[1] == (*s)[0])
// 		*s += 2;
// 	else if ((*s)[0] == '$')
// 	{
// 		ft_fprintf(2, "go_nxt_char B\n");
// 		*s += 1;
// 		while ((*s)[0] && !ft_strchr(SPE_CHAR, (*s)[0]))
// 			*s += 1;
// 	}
// 	while ((*s)[0] == ' ')
// 		*s += 1;
// 	ft_fprintf(2, "go_nxt_char3 s = |%s|\n", *s);
// }

int	get_nxt(const char *s)
{
	char	del;
	int		nxt;

	nxt = 0;
	del = ' ';
	while (s[nxt])
	{
		if (del == s[nxt] && (s[nxt] == '\"' || s[nxt] == '\''))
			del = ' ';
		else if (del == ' ' && (s[nxt] == '\"' || s[nxt] == '\''))
			del = s[nxt];
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
	ft_fprintf(2, "ICI 2 s = |%s|\n", *s);
	return (tab);
}
