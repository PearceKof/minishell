/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:23:57 by root              #+#    #+#             */
/*   Updated: 2022/12/15 14:23:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *prompt (void)
{
   char *invite = NULL;

    invite = malloc(sizeof(char *) * 2);
    strcpy(invite, ">");
    return (invite);
}

static int utils (void)
{
   int end = 0;

   while (!end)
   {
      char *s = prompt();
      printf ("%s", s);
      end++;
   }
   return 0;
}

static void sigint_handler()
{
    printf("\n");
    utils();
}

void    signaux()
{
    signal(SIGINT, sigint_handler);
}
