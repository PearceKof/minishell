/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:55:06 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/18 15:34:08 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	check_bracket(char const *s, char del, int *i)
// {
// 	if (del == s[*i] && (s[*i] == '\"' || s[*i] == '\''))
// 		del = ' ';
// 	else if (del == ' ' && (s[*i] == '\"' || s[*i] == '\''))
// 		del = s[*i];
// 	*i += 1;
// 	if (del != ' ' && s[*i] == del)
// 	{
// 		del = ' ';
// 		*i += 1;
// 	}
// 	return (del);
// }
// /*
// 	compte le nombre de string dont on aura besoin en fonction
// 	des délimiteurs (espaces ou brackets). Si à la fin del = espace. ça veut
// 	dire qu'un bracket n'est pas fermé et la ft return -1
// 	si tout s'est bien passé, return le nbr de string à allouer
// */
// static int	ft_count_space(char const *s)
// {
// 	char	del;
// 	int		count;
// 	int	i;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == ' ')
// 			i++;
// 		if (s[i] != '\0')
// 			count++;
// 		del = ' ';
// 		while (s[i] && s[i] != del)
// 			del = check_bracket(s, del, &i);
// 	}
// 	if (del != ' ')
// 		return (-1);
// 	return (count);
// }

// static const char	*dupstr_without_del(char **tab, const char *s, int i, int size)
// {
// 	char	del;
// 	int	j;
// 	int	k;

// 	*tab = (char *)malloc(sizeof(char) * (size + 1));
// 	if (!tab)
// 		return (NULL);
// 	j = 0;
// 	k = 0;
// 	while (j < i)
// 	{
// 		if (s[j] == '\"' || s[j] == '\'')
// 		{
// 			del = s[j++];
// 			while (s[j] && del != s[j] && j < i)
// 				(*tab)[k++] = s[j++];
// 		}
// 		else
// 			(*tab)[k++] = s[j++];
// 	}
// 	(*tab)[j] = '\0';
// 	return (&s[j]);
// }

// static const char	*ft_fill_tab(char **tab, const char *s)
// {
// 	char	del;
// 	int		i;
// 	int		size;

// 	i = 0;
// 	while (s[i] && s[i] == ' ')
// 		i++;
// 	size = 0;
// 	del = ' ';
// 	if ((s[i] == '\"' || s[i] == '\''))
// 		del = s[i++];
// 	while (s[i] && s[i] != del)
// 	{
// 		if (del == s[i] && (s[i] == '\"' || s[i] == '\''))
// 			del = ' ';
// 		else if (del == ' ' && (s[i] == '\"' || s[i] == '\''))
// 			del = s[i];
// 		// else if (s[i] == '$' && del != '\'')
// 		// {
// 		// 	i += var
// 		// }
// 		i++;
// 		size++;
// 		if (del != ' ' && s[i] == del)
// 		{
// 			del = ' ';
// 			i++;
// 		}
// 	}
// 	return (dupstr_without_del(tab, s, i, size));
// }
// /*
// 	Reproduit la ft split mais le délimiteur est espace. Si il y a un ' ou ",
// 	le délimiteur devient l'apostrophe en question. 
// */
// char	**split_cmd(char const *s, char **env)
// {
// 	char	**tab;
// 	int		nbrofc;
// 	int		i;

// 	(void)env;
// 	if (!s)
// 		return (NULL);
// 	nbrofc = ft_count_space(s);
// 	if (nbrofc == -1)
// 		return (NULL);
// 	tab = (char **)malloc(sizeof(char *) * (nbrofc + 1));
// 	if (!tab)
// 		return (NULL);
// 	i = 0;
// 	while (i < nbrofc)
// 	{
// 		s = ft_fill_tab(&tab[i], s);
// 		if (!tab[i])
// 			return (ft_mallerror(tab, i));
// 		i++;
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }

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
	char	*ptr;
	char	*value;
	int		i;

	ptr = NULL;
	value = NULL;
	ptr = ft_getenv(varname, env, ft_strlen(varname));
	if (!ptr)
		return (ft_strlen(varname) + 1);
	value = ft_strdup(ptr);
	i = 0;
	while (value[i])
		i++;
	free(value);
	// ft_fprintf(2, "var_value_size :|%d|\n", i);
	return (i);
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
	while (s[end] && s[end] != ' ' && s[end] != '\"' && s[end] != '\'')
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

static int	get_str_size(const char *s, char **env)
{
	char	*varname;
	char	del;
	int		i;
	int		size;

	while (*s && *s == ' ')
		s++;
	i = 0;
	size = 0;
	del = ' ';
	// ft_fprintf(2, "strsize beging with |%s|\n", &s[i]);
	if ((s[i] == '\"' || s[i] == '\''))
		del = s[i++];
	while (s[i] && s[i] != del)
	{
		if (del == s[i] && (s[i] == '\"' || s[i] == '\''))
			del = ' ';
		else if (del == ' ' && (s[i] == '\"' || s[i] == '\''))
			del = s[i];
		if (s[i] == '$' && del != '\'')
		{
			varname = isolate_varname(s, i);
			size += (var_value_size(varname, env));
			while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
				i++;
			free(varname);
			// ft_fprintf(2, "get_str_size afterdoll %d\n", size);
		}
		else
		{
			size++;
			i++;
		}
		if (del != ' ' && s[i] == del)
		{
			del = ' ';
			i++;
		}
	}
	// ft_fprintf(2, "get_str_size %d\n", size);
	return (size);
}

static char	*join_varvalue(const char **s, int *j, char *tab, int *k, char **env)
{
	char 	*ptr;
	char	*varname;
	char	*varvalue;
	int		i;

	ptr = NULL;
	varname = NULL;
	varvalue = NULL;
	varname = isolate_varname(*s, *j);
	if (!ft_getenv(varname, env, ft_strlen(varname)))
	{
		tab[*k] = '$';
		*k += 1;
		*j += 1;
		free(varname);
		return (tab);
	}
	ptr = ft_getenv(varname, env, ft_strlen(varname));
	varvalue = ft_strdup(ptr);
	i = 0;
	while (varvalue[i])
	{
		tab[*k] = varvalue[i];
		*k += 1;
		i++;
	}
	while ((*s)[*j] && (*s)[*j] != ' ' && (*s)[*j] != '\'' && (*s)[*j] != '\"')
	{
		*j += 1;
	}
	free(varvalue);
	free(varname);
	// ft_fprintf(2, "newtab = |%s|\n", tab);
	return (tab);
}

static char	*ft_fill_tab(const char **s, char **env, int size)
{
	char	*tab;
	char	del;
	int		j;
	int		k;

	// ft_fprintf(2, "malloc ft_fill_tab %d\n", size + 1);
	tab = NULL;
	tab = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	j = 0;
	k = 0;
	while (k < size && (*s)[j])
	{
		if ((*s)[j] == '\"' || (*s)[j] == '\'')
		{
			del = (*s)[j++];
			while ((*s)[j] && del != (*s)[j] && k < size)
			{
				if (del == '\"' && (*s)[j] == '$')
					tab = join_varvalue(s, &j, tab, &k, env);
				else
					tab[k++] = (*s)[j++];
			}
			j++;
		}
		else if ((*s)[j] == '$')
			tab = join_varvalue(s, &j, tab, &k, env);
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
		if (!tab[i])
			exit(EXIT_FAILURE);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}