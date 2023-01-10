/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:01:14 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/10 16:44:32 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/*
	isole le nom de la variable de la string s à partir de start
	détermine le nom en cherchant un espace/dbl quotes et alloue
	la mémoire puis renvoie le nom
	ex: echo $PATH --return--> PATH
*/
char	*isolate_varname(const char *s, int start)
{
	char	*varname;
	int		end;
	int		i;

	varname = NULL;
	start++;
	end = start;
	while (s[end] && ft_isalnum(s[end]))
		end++;
	varname = (char *)ft_calloc(sizeof(char), (end - start) + 1);
	if (!varname)
		malloc_error();
	i = 0;
	while ((i + start) < end)
	{
		varname[i] = s[i + start];
		i++;
	}
	varname[i] = '\0';
	return (varname);
}

char	*join_varvalue(const char **s, int *j, char *tab, int *k, char **env)
{
	char	*ptr;
	char	*varname;
	char	*varvalue;
	int		i;

	if ((*s)[(*j) + 1] && (*s)[(*j) + 1] == '?')
	{
		varvalue = ft_itoa(g_status);
		if (!varvalue)
			malloc_error();
		*j += 2;
	}
	else if (ft_strchr(",;", (*s)[(*j) + 1]))
	{
		varvalue = ft_strdup("$");
		if (!varvalue)
			malloc_error();
		*j += 1;
	}
	else
	{
		varvalue = NULL;
		varname = isolate_varname(*s, *j);
		ptr = ft_getenv(varname, env, ft_strlen(varname));
		free(varname);
		if (!ptr)
		{
			*j += 1;
			while ((*s)[*j] && ft_isalnum((*s)[*j]))
				*j += 1;
			// pass_until_char(*s, j, SPE_CHAR);
			return (tab);
		}
		varvalue = ft_strdup(ptr);
		if (!varvalue)
			malloc_error();
		free(ptr);
		*j += 1;
		while ((*s)[*j] && ft_isalnum((*s)[*j]))
			*j += 1;
	}
	i = 0;
	while (varvalue[i])
		tab = cpy_char(tab, k, varvalue, &i);
	free(varvalue);
	return (tab);
}
