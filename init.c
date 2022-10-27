/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:29 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/27 19:28:47 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *init_term(char **envp)
{
	t_data	*d;

	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
	{
		ft_putstr_fd("malloc failled\n", 2);
		exit(1);
	}
	d->input = NULL;
	d->end = 0;
	d->env = ft_tabdup(envp);
	if (!d->env)
		return (NULL);
	return (d);
}

t_cmd	*init_cmd(char *input)
{
	char	**input_split;
	char	**nospace_input;
	t_cmd	*c;
	size_t	i;
	size_t	size;

	input_split = ft_split(input, '|');
	i = 0;
	while (input_split[i])
	{
		if (!c)
			c = new_cmd();
		else
			c = add_cmd(c);
		nospace_input = ft_split(input_split[i], ' ');
		c = fill_cmd(nospace_input, c);
		ft_freetab(nospace_input);
		i++;
	}
	return (c);
}
