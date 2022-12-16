/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:55:06 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/16 17:00:34 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_bracket(char const *s, char del, size_t *i)
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
			del = check_bracket(s, del, &i);
	}
	if (del != ' ')
		return (-1);
	return (count);
}

int	var_value_size(char *varname, char **env)
{
	char	*value;

	value = ft_getenv(varname, env, ft_strlen(varname));
	if (!value)
		return (0);
	return (ft_strlen(value));
}
/*
	isole le nom de la variable de la string s à partir de start
	détermine le nom en cherchant un espace/dbl quotes et alloue
	la mémoire puis renvoie le nom
	ex: echo $PATH --return--> PATH
*/
static char	*isolate_varname(const char *s, int start)
{
	char	*varname;
	int		end;
	int		i;

	end = start;
	while (s[end] && s[end] != ' ' && s[end] != '\"')
		end++;
	varname = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (!varname)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while ((i + start) < end)
	{
		varname[i] = s[i + start];
		i++;
	}
	varname[i] = '\0';
	return (varname);
}

static int	get_str_size(const char *s, char **env)
{
	char	del;
	int		i;
	int		size;

	while (*s && *s == ' ')
		s++;
	i = 0;
	size = 0;
	del = ' ';
	if ((*s == '\"' || *s == '\''))
		del = s[i++];
	while (s[i] && s[i] != del)
	{
		if (del == s[i] && (s[i] == '\"' || s[i] == '\''))
			del = ' ';
		else if (del == ' ' && (s[i] == '\"' || s[i] == '\''))
			del = s[i];
		else if (s[i] == '$' && del != '\'')
		{
			size += var_value_size(isolate_varname(s, i + 1), env);
		}
		i++;
		size++;
		if (del != ' ' && s[i] == del)
		{
			del = ' ';
			i++;
		}
	}
	return (size);
}

static char	*ft_fill_tab(const char **s, char **env, int size)
{
	char	*tab;
	char	del;
	int		j;
	int		k;

	(void)env;
	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (!tab)
		return (NULL);
	j = 0;
	k = 0;
	while (j < size)
	{
		if ((*s)[j] == '\"' || (*s)[j] == '\'')
		{
			del = (*s)[j++];
			while ((*s)[j] && del != (*s)[j] && j < size)
				tab[k++] = (*s)[j++];
		}
		else
			tab[k++] = (*s)[j++];
	}
	tab[k] = '\0';
	(*s) += j;
	return (tab);
}
/*
	Reproduit la ft split mais le délimiteur est espace. Si il y a un ' ou ",
	le délimiteur devient l'apostrophe en question. 
*/
char	**split_cmd(char const *s, char **env)
{
	char	**tab;
	int		nbrofc;
	int		i;

	if (!s)
		return (NULL);
	nbrofc = ft_count_space(s);
	if (nbrofc == -1)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (nbrofc + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < nbrofc)
	{
		while (*s && *s == ' ')
			s++;
		tab[i] = ft_fill_tab(&s, env, get_str_size(s, env));
		ft_fprintf(2, "tab = |%s|\n\n", tab[i]);
		if (!tab[i])
			return (ft_mallerror(tab, i));
		i++;
	}
	tab[i] = NULL;
	return (tab);
}