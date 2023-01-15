/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:10:23 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/15 20:35:51 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

char	*ft_read(void)
{
	char	*buf;
	char	*line;
	char	*tmp;
	int		end;

	end = 1;
	buf = ft_calloc(2, sizeof(char));
	line = ft_calloc(2, sizeof(char));
	while (!ft_strchr(buf, '\n') && end != 0)
	{
		end = read(0, buf, 1);
		if (g_status == 130)
		{
			free(line);
			break;
		}
		else if (buf[0] == '\n')
			break;
		buf[end] = '\0';
		tmp = ft_strjoin(line, buf);
		if (!tmp)
			malloc_error();
		free(line);
		line = ft_strdup(tmp);
		free(tmp);
	}
	free(buf);
	return (line);
}