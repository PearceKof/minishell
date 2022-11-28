/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:47:18 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/28 17:16:34 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;
/*
vérifie que l'input à bien été lu et l'enregistre
dans l'historique si c'est le cas
*/
static	int	input_check(t_data *d)
{
	if (!d->input)
	{
		ft_putstr_fd("exit\n", 2);
		ft_freetab(d->env);
		free(d);
		exit(0);
	}
	if (d->input[0] == '\0')
		return (0);
	add_history(d->input);
	return (1);
}
/*
affiche les infos de la commande c en argumant
Juste pour debugger
*/
void	printcmd(t_cmd *c)
{
	int i;
	int j;

	while (c)
	{
		printf("prev: %p\n", c->prev);
		printf("----->%p\n", c);
		printf("next: %p\n", c->next);
		printf("in : %d out : %d\n", c->in, c->out);
		i = 0;
		while (c->full_cmd[i])
		{
			j = 0;
			while (c->full_cmd[i][j])
			{
				printf("%c", c->full_cmd[i][j]);
				j++;
			}
			printf("|\n-------\n|");
			i++;
		}
		c = c->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_data	*d;
	t_cmd	*c;

	d = init_term(envp);
	if (!d)
		return (1);
	while (ac && av)
	{
		d->input = readline(">");
		if (input_check(d))
		{
			c = init_cmd(d->input);
			if (c)
			{
				printcmd(c);
				execute(envp, c);
				free_cmd(c);
			}
		}
		free(d->input);
	}
}
