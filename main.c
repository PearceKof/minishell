/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:47:18 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/27 19:26:54 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

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
			execute(envp, d->input);
		}
		free(d->input);
	}
}
