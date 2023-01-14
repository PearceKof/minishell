/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:35:06 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/14 15:47:39 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

t_cmd	*heredoc_attempt(char **env, char *s, int *i, t_cmd *last)
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

static char	*parse_heredoc(char *buf, char **env)
{
	int		i;
	int		j;
	char	*new_buf;

	i = 0;
	j = 0;
	new_buf = malloc(sizeof(char) * (get_line_size(buf, env) + 1));
	while (buf[i])
	{
		if (buf[i] == '$' && !ft_strchr(" ", buf[i + 1]))
			new_buf = join_varvalue(new_buf, &j, get_var_value(buf, &i, env));
		else
			new_buf = cpy_char(new_buf, &j, buf, &i);
	}
	free(buf);
	new_buf[j] = '\0';
	return (new_buf);
}

static char	*read_until_del(char *s, char *delimiter, char **env)
{
	char	*buf;
	char	*tmp;

	g_status = 0;
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
	return (s);
}

static void	heredoc_childprocess(char **env, char *delimiter, int *fd)
{
	char	*s;

	signal(SIGINT, sigint_in_heredoc_handler);
	s = ft_calloc(sizeof(char), 1);
	if (!s)
		malloc_error();
	s = read_until_del(s, delimiter, env);
	write(fd[1], s, ft_strlen(s));
	free(s);
	exit(g_status);
}

t_cmd	*ft_heredoc(t_cmd *c, char *delimiter, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		error(PIPERR, 1, NULL, NULL);
		return (c);
	}
	pid = fork();
	if (pid == -1)
	{
		error(FORKERR, 1, NULL, NULL);
		return (c);
	}
	if (pid == 0)
		heredoc_childprocess(env, delimiter, fd);
	waitpid(pid, &g_status, 0);
	close(fd[1]);
	g_status = WEXITSTATUS(g_status);
	c->in = fd[0];
	return (c);
}
