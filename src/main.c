/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:47:18 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/09 16:39:07 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	exit_test(void)
{
	exit(g_status);
}

/*
	check si l'argument s contient autre chose que des caractéres "vides"
	" \t\n\v\f\r\'\""
	return 
*/
int	is_only_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strchr(" \t\n\v\f\r", s[i]))
			return (0);
		i++;
	}
	return (1);
}
/*
vérifie que l'input à bien été lu et qu'il contient bien une commande
enregistre dans l'historique si la commande est correct
return 1 si l'input est correct
return 0 si incorrect
*/

static	int	is_correct_input(char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (is_heredoc(input))
		ft_fprintf(2, "HEREDOC\n");
	else if (is_only_space(input) || input[0] == '\0' || is_invalid_syntax(input))
		return (0);
	add_history(input);
	return (1);
}
/*
affiche les infos de la commande c en argumant
Juste pour debugger
*/
/*
void	printcmd(t_cmd *c)
{
	int	i;
	int	j;

	while (c)
	{
		ft_fprintf(2, "prev: %p\n", c->prev);
		ft_fprintf(2, "----->%p\n", c);
		ft_fprintf(2, "next: %p\n", c->next);
		ft_fprintf(2, "in : %d out : %d\n", c->in, c->out);
		i = 0;
		while (c->full_cmd[i])
		{
			j = 0;
			ft_fprintf(2, "|");
			while (c->full_cmd[i][j])
			{
				ft_fprintf(2, "%c", c->full_cmd[i][j]);
				j++;
			}
			ft_fprintf(2, "|\n-------\n");
			i++;
		}
		c = c->next;
	}
}
*/
int	main(int ac, char **av, char **envp)
{
	t_data	d;
	t_cmd	*c;

	d = init_term(av, envp, d);
	g_status = 0;
	while (ac && av)
	{
		signal(SIGINT, sigint_handler);
		d.input = readline("=>");
		if (is_correct_input(d.input))
		{
			c = init_cmd(d.input, d.env);
			if (c)
			{
				//printcmd(c);
				execute(c, &d);
				free_cmd(c);
			}
		}
		free(d.input);
	}
}
