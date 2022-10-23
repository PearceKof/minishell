/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:47:18 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/23 17:37:15 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern int g_status;

static	int	input_check(t_data *d)
{
	if (d->input[0] == '\0')
		return (0);
	if (!d->input)
	{
		ft_putstr_fd("exit\n", 2);
		ft_freetab(d->env);
		free(d);
		exit(0);
	}
	// add_to_historic(d->input);
	return (1);
}

int main(int ac, char **av, char **envp)
{
	t_data	*d;

	d = init_term(envp);
	if (!d)
		return (1);
	while (ac && av)
	{
		write(1, ">", 1);
		d->input = get_input();
		if (input_check(d))
		{
			
			execute(envp, d->input);
		}
		free(d->input);
	}
}
