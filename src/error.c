/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:59:32 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/17 14:53:50 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static char	*error_type(int errorid)
{
	static char	error[20][50];

	ft_strlcpy(error[QUOTEUNCLOSED], ": Closing quote not found\n", 50);
	ft_strlcpy(error[NL], "syntax error near unexpected token `newline'\n", 50);
	ft_strlcpy(error[PIPEUNCLOSED], "Input end with unclosed pipe\n", 50);
	ft_strlcpy(error[NDIR], ": No such file or directory\n", 50);
	ft_strlcpy(error[NPERM], ": Permission denied\n", 50);
	ft_strlcpy(error[PIPERR], "error creating pipe\n", 50);
	ft_strlcpy(error[FORKERR], "fork failed\n", 50);
	ft_strlcpy(error[NCMD], ": command not found\n", 50);
	ft_strlcpy(error[INVID], ": not a valid identifier\n", 50);
	ft_strlcpy(error[HNOSET], ": HOME not set\n", 50);
	ft_strlcpy(error[TOOARGS], ": too many arguments\n", 50);
	ft_strlcpy(error[NUMARGS], ": numeric argument required\n", 50);
	ft_strlcpy(error[ISDIR], ": is a directory\n", 50);
	return (error[errorid]);
}

int	error(int errorid, int error_status, char *infoa, char *infob)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(infoa, 2);
	if (errorid)
		ft_putstr_fd(infob, 2);
	else
		perror(infob);
	ft_putstr_fd(error_type(errorid), 2);
	g_status = error_status;
	return (error_status);
}

void	malloc_error(void)
{
	ft_putstr_fd("minishell: malloc failed\nexit\n", 2);
	exit(EXIT_FAILURE);
}
