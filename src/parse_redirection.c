/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:40:48 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/13 19:01:55 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

extern int	g_status;

char	*get_file_name(char *s, int i, int size, char **env)
{
	char	*file_name;
	char	del;
	int		j;

	file_name = malloc(sizeof(char) * (size + 1));
	if (!file_name)
		malloc_error();
	del = ' ';
	j = 0;
	while (j < size && s[i])
	{
		if (del != new_delimiter(del, s[i]))
		{
			del = new_delimiter(del, s[i]);
			i++;
		}
		else if (s[i] == '$' && ft_isalnum(s[i + 1]) && del != '\'')
			file_name = join_varvalue(file_name, &j, get_var_value(s, &i, env));
		else
			file_name = cpy_char(file_name, &j, s, &i);
	}
	file_name[j] = '\0';
	return (file_name);
}

/*
	prends le pointeur sur s et la redirection red que l'on cherche,
	return 0 si il y a encore au moins une redirection
	return 1 si il n'y en a plus.
*/
// static int	no_more_red(char *s, char red, int i)
// {
// 	char	del;

// 	i++;
// 	del = ' ';
// 	while (s && s[i])
// 	{
// 		if (del != new_delimiter(del, s[i]))
// 			del = new_delimiter(del, s[i]);
// 		else if ((s[i]) == red && del == ' ')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

static t_cmd	*open_file(t_cmd *c, char *file_name, char red_type)
{
	if (red_type == '<'&& c->in != -1)
	{
		if (c->in != 0)
			close(c->in);
		c->in = open(file_name, O_RDONLY);
		if (c->in == -1)
			error(NDIR, 1, file_name, NULL);
	}
	else if (red_type == '>' && c->out != -1)
	{
		if (c->out != 1)
			close(c->out);
		c->out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 00777);
		if (c->out == -1)
			error(NPERM, 1, file_name, NULL);
	}
	return (c);
}

static t_cmd *open_attempt(char **env, char *s, int *i, t_cmd *last)
{
	int		red_pos;
	int		red_type;
	char	*file_name;
	int		nxt;

	red_type = s[*i];
	red_pos = *i;
	pass_while_char(s, i, " ");
	nxt = get_nxt(&s[*i]);
	file_name = get_file_name(s, *i, file_name_size(s, *i, env), env);
	*i += nxt;
	replace_with_space(&s, red_pos, i);
	last = open_file(last, file_name, red_type);
	if (file_name)
		free(file_name);
	return (last);
}

t_cmd	*redirection(t_cmd *c, t_cmd *last, char *s, char **env)
{
	char	del;
	int		i;

	i = 0;
	del = ' ';
	last = get_last_cmd(c);
	while (s && s[i])
	{
		del = new_delimiter(del, s[i]);
		if ((s[i] == '<' || s[i] == '>') && s[i + 1] != s[i] && del == ' ')
			last = open_attempt(env, s, &i, last);
		else if(s[i] == '<' && s[i + 1] == s[i] && del == ' ')
		{
			last = heredoc_attempt(env, s, &i, last);
			if (g_status == 130)
			{
				free_cmd(c);
				return (NULL);
			}
			return (c);
		}
		i++;
	}
	return (c);
}
