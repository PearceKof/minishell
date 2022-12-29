/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:36:53 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/29 18:06:07 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	nxt_del(char const *s, char del, size_t *i)
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
/*
	compte le nombre de string dont on aura besoin en fonction
	des délimiteurs (espaces ou brackets). Si à la fin del = espace. ça veut
	dire qu'un bracket n'est pas fermé et la ft return -1
	si tout s'est bien passé, return le nbr de string à allouer
*/
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
			del = nxt_del(s, del, &i);
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
	nbrofc = ft_count_space(s);
	ft_fprintf(2, "nbrofc: %d\n", nbrofc);
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
