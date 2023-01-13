/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:36:53 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/13 22:16:53 by blaurent         ###   ########.fr       */
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

static int	is_env_var(char **s, int *i, char **env)
{
	char	*varname;
	char	*varvalue;
	int		is_in_env;
	int		j;

	varname = isolate_varname((*s), *i);
	varvalue = ft_getenv(varname, env, ft_strlen(varname));
	if (!varvalue)
	{
		j = 0;
		while (varname[j])
		{
			(*s)[(*i) + j] = ' ';
			j++;
			(*s)[(*i) + j] = ' ';
		}
	}
	free(varname);
	is_in_env = 0;
	if (varvalue)
		is_in_env = 1;
	free(varvalue);
	return (is_in_env);
}
/*
	compte le nombre de string dont on aura besoin en fonction
	des délimiteurs (espaces ou brackets). Si à la fin del = espace. ça veut
	dire qu'un bracket n'est pas fermé et la ft return -1
	si tout s'est bien passé, return le nbr de string à allouer
*/
static int	ft_count_space(char *s, char **env)
{
	char	del;
	int		count;
	int		i;

	i = 0;
	count = 0;
	del = ' ';
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '$' && ft_isalnum(s[i + 1]) && del != '\'')
			count += is_env_var(&s, &i, env);
		else if (s[i] != '\0')
			count++;
		del = ' ';
		while (s[i] != del && s[i] != '\0')
			del = nxt_del((const char *)s, del, ' ', &i);
	}
	if (is_only_space(s))
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
	tab = fill_tab(tab, s, env, size);
	return (tab);
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
