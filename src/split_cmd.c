/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:55:06 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/21 17:40:32 by blaurent         ###   ########.fr       */
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

	varname = NULL;
	start++;
	end = start;
	while (s[end] && s[end] != ' ' && s[end] != '\"' && s[end] != '\'' && s[end] != '$')
		end++;
	varname = (char *)ft_calloc(sizeof(char), (end - start) + 1);
	if (!varname)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	// ft_fprintf(2, "malloc isolatevarname %d\n", (end - start) + 1);
	i = 0;
	while ((i + start) < end)
	{
		varname[i] = s[i + start];
		i++;
	}
	varname[i] = '\0';
	return (varname);
}

int	var_value_size(char **env, const char *s, int *i, char del)
{
	char	*varname;
	char	*ptr;
	char	*value;
	int		size;

	varname = isolate_varname(s, *i);
	*i += 1;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\'' && s[*i] != '\"' && s[*i] != '$')
		*i += 1;
	ptr = ft_getenv(varname, env, ft_strlen(varname));
	size = ft_strlen(varname) + 1;
	free(varname);
	if (!ptr && del == ' ')
		return (size);
	else if (!ptr && del != ' ')
		return (0);
	value = ft_strdup(ptr);
	if (!value)
		exit(EXIT_FAILURE);
	size = ft_strlen(value);
	free(value);
	// ft_fprintf(2, "var_value_size :|%d|\n", i);
	return (size);
}

static int	get_str_size(const char *s, char **env, char del)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i] && s[i] != del)
	{
		ft_fprintf(2, "size: %d s: |%s|\ndel: |%c|\n", size, &s[i], del);
		if (del == s[i] && (s[i] == '\"' || s[i] == '\''))
			del = ' ';
		else if (del == ' ' && (s[i] == '\"' || s[i] == '\''))
			del = s[i];
		else if (s[i] != '$' || del == '\'')
			size++;
		if (s[i] == '$' && del != '\'')
			size += var_value_size(env, s, &i, del);
		else
			i++;
		if (del != ' ' && s[i] == del)
		{
			del = ' ';
			i++;
		}
	}
	ft_fprintf(2, "get_str_size %d\n", size);
	return (size);
}

static char	*join_varvalue_quote(const char **s, int *j, char *tab, int *k, char **env)
{
	char	*ptr;
	char	*varname;
	char	*varvalue;
	int		i;

	varvalue = NULL;
	varname = isolate_varname(*s, *j);
	ptr = ft_getenv(varname, env, ft_strlen(varname));
	if (!ptr)
	{
		while ((*s)[*j] && (*s)[*j] != '\"' && (*s)[*j] != ' ')
			*j += 1;
		free(varname);
		return (tab);
	}
	varvalue = ft_strdup(ptr);
	i = 0;
	while (varvalue[i])
	{
		tab[*k] = varvalue[i];
		*k += 1;
		i++;
	}
	*j += 1;
	while ((*s)[*j] && (*s)[*j] != ' ' && (*s)[*j] != '\'' && (*s)[*j] != '\"' && (*s)[*j] != '$')
		*j += 1;
	free(varvalue);
	free(varname);
	// ft_fprintf(2, "newtab = |%s|\n", tab);
	return (tab);
}

static char	*join_varvalue(const char **s, int *j, char *tab, int *k, char **env)
{
	char	*ptr;
	char	*varname;
	char	*varvalue;
	int		i;

	varvalue = NULL;
	varname = isolate_varname(*s, *j);
	ptr = ft_getenv(varname, env, ft_strlen(varname));
	if (!ptr)
	{
		tab[*k] = '$';
		*k += 1;
		*j += 1;
		free(varname);
		return (tab);
	}
	varvalue = ft_strdup(ptr);
	i = 0;
	while (varvalue[i])
	{
		tab[*k] = varvalue[i];
		*k += 1;
		i++;
	}
	*j += 1;
	while ((*s)[*j] && (*s)[*j] != ' ' && (*s)[*j] != '\'' && (*s)[*j] != '\"' && (*s)[*j] != '$')
		*j += 1;
	free(varvalue);
	free(varname);
	// ft_fprintf(2, "newtab = |%s|\n", tab);
	return (tab);
}
static char	*fill_tab(char *tab, const char **s, char **env, int size)
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
				if (del == '\"' && (*s)[j] == '$')
					tab = join_varvalue_quote(s, &j, tab, &i, env);
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
	(*s) += j;
	if (((*s)[0] == '\'' || (*s)[0] == '\"') && (*s)[1] == (*s)[0])
		(*s) += 2; 
	return (tab);
}

static char	*malloc_and_fill_tab(const char **s, char **env, int size)
{
	char	*tab;

	// ft_fprintf(2, "malloc ft_fill_tab %d\n", size + 1);
	tab = NULL;
	tab = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	return (fill_tab(tab, s, env, size));
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
	ft_fprintf(2, "nbrofc: %d\n", nbrofc);
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
		tab[i] = malloc_and_fill_tab(&s, env, get_str_size(s, env, ' '));
		ft_fprintf(2, "loop tab: |%s| s: |%s|\n", tab[i], s);
		if (!tab[i])
			exit(EXIT_FAILURE);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}