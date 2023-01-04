/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:40:48 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/03 20:51:03 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

extern int	g_status;

static char	*get_file_name(char *s, char red, int *i, int size)
{
	char	*file_name;
	char	del;
	int		j;

	file_name = malloc(sizeof(char) * (size + 1));
	if (!file_name)
		malloc_error();
	*i += 1;
	while (s[*i] && s[*i] == ' ')
		*i += 1;
	del = ' ';
	if (s[*i] && (s[*i] == '\'' || s[*i] == '\"'))
	{
		del = s[*i];
		*i += 1;
	}
	j = 0;
	while (s[*i] && s[*i] != red && s[*i] != del
		&& !ft_strchr("$\\#=[]!|;{}()*?~&+-", s[*i]))
		file_name = cpy_char(file_name, &j, s, i);
	file_name_uts(s, red, i);
	file_name[j] = '\0';
	return (file_name);
}

/*
	prends le pointeur sur s et la redirection red que l'on cherche,
	return 0 si il y a encore des redirections
	return 1 si il n'y en a plus.
*/
static int	no_more_red(char *s, char red)
{
	char	del;
	int		i;

	i = 0;
	del = ' ';
	while (s[i])
	{
		if (del == ' ' && (s[i] == '\'' || s[i] == '\"'))
			del = s[i];
		else if (del == s[i] && (s[i] == '\'' || s[i] == '\"'))
			del = ' ';
		else if ((s[i]) == red && del == ' ')
			return (0);
		i++;
	}
	return (1);
}

static t_cmd	*open_file(t_cmd *c, char *file_name, char red, char *s)
{
	if (red == '<')
	{
		if (c->in != 0 && c->in != -1)
			close(c->in);
		c->in = open(file_name, O_RDONLY);
		if (c->in == -1 && no_more_red(s, red))
			error(NDIR, 1, file_name, NULL);
	}
	else if (red == '>')
	{
		if (c->out != 1 && c->out != -1)
			close(c->out);
		c->out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 00777);
		if (c->out == -1 && no_more_red(s, red))
			error(NPERM, 1, file_name, NULL);
	}
	return (c);
}

t_cmd	*redirection(t_cmd *c, char *s)
{
	t_cmd	*ptr;
	char	*file_name;
	char	del;
	char	red;
	int		i;

	ptr = ptr_utls(c);
	i = 0;
	del = ' ';
	while (s[i])
	{
		if ((s[i] == '<' || s[i] == '>') && del == ' ')
		{
			redi_utls(del, i, s);
			red = s[i];
			file_name = get_file_name(s, s[i], &i, file_name_size(s, s[i], i));
			ft_fprintf(2, "\n\nFILE_NAME HERE |%s|\n\ns= |%s||%s|\n\n",
				file_name, &s[i], s);
			ptr = open_file(ptr, file_name, red, &s[i]);
			if (file_name)
				free(file_name);
		}
		i++;
	}
	return (c);
}
