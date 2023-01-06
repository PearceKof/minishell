/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:29 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/06 19:20:36 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(char *input, char **env)
{
	char	**input_split;
	t_cmd	*c;
	int		i;

	c = NULL;
	i = 0;
	input_split = parse_pipe(input);
	if (!input_split)
	{
		error(PIPEND, 2, NULL, NULL);
		return (NULL);
	}
	while (input_split[i])
	{
		c = create_cmdlist(input_split[i], c, env);
		if (!c)
		{
			ft_freetab(input_split);
			return (NULL);
		}
		i++;
	}
	ft_freetab(input_split);
	return (c);
}

t_data	*init_term(char **av, char **envp)
{
	t_data	*d;

	d = NULL;
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
	{
		ft_putstr_fd("malloc failled\n", 2);
		exit(1);
	}
	d->index = 1;
	d->input = NULL;
	d->env = ft_tabdup(envp);
	d->env = init_env(av, d);
	if (!d->env)
		exit(EXIT_FAILURE);
	return (d);
}
