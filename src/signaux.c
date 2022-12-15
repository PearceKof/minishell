/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:23:57 by root              #+#    #+#             */
/*   Updated: 2022/12/15 16:19:55 by blaurent         ###   ########.fr       */
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
	check si le signal est le bon et passe à la ligne
	affiche le prompt à la ligne suivante
	nettoie la ligne
	puis réaffiche le prompt
*/
static void sigint_handler(int sig)
{
    pid_t   pid;
    int     states;

    pid = waitpid(-1, &states, WNOHANG);
	if (sig == SIGINT)
	{
        if (pid == -1)
		{
			write(1, "\n", 1);
		    rl_on_new_line();
		    rl_replace_line("", 0);
		    rl_redisplay();
		    g_status = 130;
		}
		else
			write(1, "\n", 1);
	}
}

void    signaux()
{
    signal(SIGINT, sigint_handler);
}
