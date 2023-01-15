/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:04:49 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/15 23:29:38 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static t_cmd	*open_file_append(t_cmd *c, char *file_name)
{
	c->out = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (c->out == -1)
		error(NPERM, 1, file_name, NULL);
	return (c);
}

t_cmd	*open_attempt_append(char *s, int *i, t_cmd *last)
{
	int		red_pos;
	char	*delimiter;
	int		nxt;

	if (&s[*i] == NULL && !is_only_space(s) && s[*i] == '>' && s[*i + 1] == s[*i])
	{
		red_pos = *i;
		*i += 1;
		pass_while_char(s, i, " ");
		nxt = get_nxt(&s[*i]);
		delimiter = get_delimiter(s, *i, delimiter_size(s, *i));
		last = open_file_append(last, delimiter);
		*i += nxt;
		replace_with_space(&s, red_pos, i);
		free(delimiter);
	}
	return (last);
}
