/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:35:06 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/13 18:59:33 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

// char	*get_limiter(char *s, char **env)
// {
// 	char	del;
// 	int		i;
// 	char	*limiter;

// 	i = 0;
// 	del = ' ';
// 	while (s && s[i])
// 	{
// 		del = new_delimiter(del, s[i]);
// 		if ((s[i] == '<' && s[i + 1] == '<') && del == ' ')
// 		{
// 			i += 1;
// 			pass_while_char(s, &i, " ");
// 			limiter = get_file_name(s, i, file_name_size(s, i, env), env);
// 		}
// 		i++;
// 	}
// 	return (limiter);
// }
int	delimiter_size(const char *s, int i)
{
	int		size;
	char	del;

	del = ' ';
	size = 0;
	while (s[i] && !ft_strchr("<>|;()?&", s[i]))
	{
		if (del != new_delimiter(del, s[i]))
			del = new_delimiter(del, s[i]);
		else
			size++;
		i++;
		if (del != ' ' && s[i] == del)
		{
			del = ' ';
			i++;
		}
		if (s[i] == ' ' && del == ' ')
			break;
	}
	return (size);
}

char	*get_delimiter(char *s, int i, int size)
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
		else
			file_name = cpy_char(file_name, &j, s, &i);
	}
	file_name[j] = '\0';
	return (file_name);
}

t_cmd *heredoc_attempt(char **env, char *s, int *i, t_cmd *last)
{
	int		red_pos;
	char	*delimiter;
	int		nxt;

	red_pos = *i;
	*i += 1;
	pass_while_char(s, i, " ");
	nxt = get_nxt(&s[*i]);
	delimiter = get_delimiter(s, *i, delimiter_size(s, *i));
	last = ft_heredoc(last, delimiter, env);
	*i += nxt;
	replace_with_space(&s, red_pos, i);
	free(delimiter);
	return (last);
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*parse_heredoc(char *buf, char **env)
{
	int		i;
	int		j;
	char	del;
	char	*new_buf;

	i = 0;
	j = 0;
	del = ' ';
	new_buf = malloc(sizeof(char) * (get_str_size(buf, env, ' ') + 1));
	while (buf[i])
	{
		if (del != new_delimiter(del, buf[i]))
		{
			del = new_delimiter(del, buf[i]);
			j++;
		}
		else if (buf[i] == '$' && del != '\'' && !ft_strchr(" ", buf[i + 1]))
			new_buf = join_varvalue(new_buf, &j, get_var_value(buf, &i, env));
		else
			new_buf = cpy_char(new_buf, &j, buf, &i);
	}
	free(buf);
	new_buf[j] = '\0';
	// ft_fprintf(2, "new_buf |%s|\n", new_buf);
	return (new_buf);
}

char	*read_until_del(char *s, char *delimiter, char **env)
{
	char	*buf;
	char	*tmp;

	g_status = 0;
	ft_fprintf(2, "delimiter |%s|\n", delimiter);
	while (g_status != 130)
	{
		buf = readline("> ");
		if (!buf)
			write(1, "\n", 1);
		if (!buf || !ft_strcmp(buf, delimiter))
		{
			if (buf)
				free(buf);
			break ;
		}
		buf = parse_heredoc(buf, env);
		tmp = buf;
		buf = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = s;
		s = ft_strjoin(tmp, buf);
		free(tmp);
		free(buf);
	}
	ft_fprintf(2, "g_status %d\n", g_status);
	return (s);
}

t_cmd	*ft_heredoc(t_cmd *c, char *delimiter, char **env)
{
	pid_t	pid;
	char	*s;
	int		fd[2];

	ft_fprintf(2, "g_status %d\n", g_status);
	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		error(FORKERR, 1, NULL, NULL);
		return(c);
	}
	if (pid == 0)
	{
		signal(SIGINT, sigint_in_heredoc_handler);
		s = ft_calloc(sizeof(char), 1);
		if (!s)
			malloc_error();
		s = read_until_del(s, delimiter, env);
		write(fd[1], s, ft_strlen(s));
		free(s);
		exit(g_status);
	}
	waitpid(pid, &g_status, 0);
	close(fd[1]);
	g_status = WEXITSTATUS(g_status);
	c->in = fd[0];
	return (c);
}



int	is_heredoc(char *input)
{
	int	hdoc_char;
	int	i;

	i = 0;
	hdoc_char = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			pass_while_char(input, &i, " ");
			if (input[i] == '\0')
			{
				error(NL, 2, NULL, NULL);
				return (-1);
			}
			hdoc_char = 1;
		}
		if (ft_isalpha(input[i]) && hdoc_char)
			return (1);
		i++;
	}
	return (0);
}