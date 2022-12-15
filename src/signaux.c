/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:23:57 by root              #+#    #+#             */
/*   Updated: 2022/12/15 16:15:19 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

// char *prompt (void)
// {
//    char *invite = NULL;

//     invite = malloc(sizeof(char *) * 2);
//     strcpy(invite, ">");
//     return (invite);
// }

// static int utils (void)
// {
//    int end = 0;

//    while (!end)
//    {
//       char *s = prompt();
//       printf ("%s", s);
//       end++;
//    }
//    return (0);
// }
/*

*/
static void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}

void    signaux()
{
    signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
