/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:10:23 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/15 21:47:02 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;



// char	*ft_read(void)
// {
// 	char	*buf;
// 	char	*line;
// 	char	*tmp;

// 	buf = readline("> ");
// 	ft_fprintf(2, "buf= |%s|\n", buf);
// 	if (g_status == 130)
// 	{
// 		ft_fprintf(2, "DEBUG\n");
// 		free(line);
// 		free(buf);
// 		return (NULL);
// 	}
// 		// if (!buf || g_status == 130)
// 		// 	break;
// 		tmp = ft_strjoin(line, buf);
// 		if (!tmp)
// 			malloc_error();
// 		free(line);
// 		line = ft_strdup(tmp);
// 		free(tmp);
// 	}
// 	free(buf);
// 	return (line);
// }