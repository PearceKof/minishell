/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:01:14 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/17 13:34:53 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*isolate_varname(const char *s, int start)
{
	char	*varname;
	int		end;
	int		i;

	varname = NULL;
	start++;
	end = start;
	while (!ft_strchr(" \'\"", s[end]) && ft_isalnum(s[end]))
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

static char	*find_var_value(const char *s, int *j, char **env)
{
	char	*ptr;
	char	*varname;
	char	*varvalue;

	varvalue = NULL;
	varname = isolate_varname(s, *j);
	ptr = ft_getenv(varname, env, ft_strlen(varname));
	free(varname);
	if (ptr)
	{
		varvalue = ft_strdup(ptr);
		free(ptr);
	}
	pass_while_isalnum(s, j);
	return (varvalue);
}

char	*get_var_value(const char *s, int *j, char **env)
{
	char	*varvalue;

	if (s[(*j) + 1] && s[(*j) + 1] == '?')
	{
		varvalue = ft_itoa(g_status);
		if (!varvalue)
			malloc_error();
		*j += 2;
	}
	else if ((ft_strchr(" ", s[(*j) + 1]) || !ft_isalnum(s[(*j) + 1]))
		&& !ft_strchr("\"\'", s[(*j) + 1]))
	{
		varvalue = ft_strdup("$");
		*j += 1;
	}
	else
		varvalue = find_var_value(s, j, env);
	return (varvalue);
}

char	*join_varvalue(char *tab, int *k, char *varvalue)
{
	int		i;

	i = 0;
	if (!varvalue)
		return (tab);
	while (varvalue[i])
		tab = cpy_char(tab, k, varvalue, &i);
	tab[*k] = '\0';
	free(varvalue);
	return (tab);
}
