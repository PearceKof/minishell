/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:36:53 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/10 15:23:24 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	nxt_del(char const *s, char del, char dfdel, int *i)
{
	if (del == s[*i] && (s[*i] == '\"' || s[*i] == '\''))
		del = dfdel;
	else if (del == dfdel && (s[*i] == '\"' || s[*i] == '\''))
		del = s[*i];
	*i += 1;
	if (del != dfdel && s[*i] == del)
	{
		del = dfdel;
		*i += 1;
	}
	return (del);
}
/*
	compte le nombre de string dont on aura besoin en fonction
	des délimiteurs (espaces ou brackets). Si à la fin del = espace. ça veut
	dire qu'un bracket n'est pas fermé et la ft return -1
	si tout s'est bien passé, return le nbr de string à allouer
*/

// int	is_existing_value(const char *s, )

static int	ft_count_space(char *s, char **env)
{
	char	del;
	int		count;
	int		i;
	int		j;
	char	*tmp;
	char	*varvalue;

	i = 0;
	count = 0;
	del = ' ';
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '$' && ft_isalnum(s[i + 1]) && del != '\'')
		{
			tmp = isolate_varname(s, i);
			varvalue = ft_getenv(tmp, env, ft_strlen(tmp));
			j = 0;
			if (!varvalue)
			{
				while (tmp[j])
				{
					s[i + j] = ' ';
					j++;
					s[i + j] = ' ';
				}
			}
			free(tmp);
			if (varvalue)
				count++;
			free(varvalue);
		}
		else if (s[i] != '\0')
			count++;
		del = ' ';
		while (s[i] != del && s[i] != '\0')
			del = nxt_del((const char *)s, del, ' ', &i);
	}
	if (del != ' ')
		return (-1);
	return (count);
}

static char	*malloc_and_fill_tab(const char **s, char **env, int size)
{
	char	*tab;

	tab = NULL;
	tab = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!tab)
		malloc_error();
	return (fill_tab(tab, s, env, size));
}
/*
	parsing de l'input, alloue la mémoire et return un char** créé à partir
	de l'argument s si tout s'est bien passé. sinon, il renvoi NULL
*/

char	**parse_cmd(char const *s, char **env)
{
	char	**tab;
	int		nbrofc;
	int		i;

	if (!s)
		return (NULL);
	nbrofc = ft_count_space((char *)s, env);
	if (nbrofc == -1)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (nbrofc + 1));
	if (!tab)
		malloc_error();
	i = 0;
	while (i < nbrofc)
	{
		while (s && *s == ' ')
			s++;
		tab[i] = malloc_and_fill_tab(&s, env, get_str_size(s, env, ' '));
		if (!tab[i])
			malloc_error();
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
