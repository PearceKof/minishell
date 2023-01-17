/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:29 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/17 13:22:31 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	init_pwd(t_data d)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	d.env = set_env_var("PWD", tmp, &d, 3);
	free(tmp);
	return (d);
}

static t_data	init_vars(t_data d, char **av, char *str, char *tmp)
{
	str = ft_getenv("SHLVL", d.env, 5);
	if (!str || ft_atoi(str) <= 0)
		tmp = ft_strdup("1");
	else
	{
		tmp = ft_itoa(ft_atoi(str) + 1);
		if (!tmp)
			malloc_error();
	}
	if (str)
		free(str);
	d.env = set_env_var("SHLVL", tmp, &d, 5);
	free(tmp);
	str = ft_getenv("PATH", d.env, 4);
	if (!str)
		d.env = set_env_var("PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", &d, 4);
	else
		free(str);
	str = ft_getenv("_", d.env, 1);
	if (!str)
		d.env = set_env_var("_", av[0], &d, 1);
	else
		free(str);
	return (d);
}

t_cmd	*init_cmd(char *input, t_data *d)
{
	char	**input_btw_pipe;
	t_cmd	*c;
	int		i;

	c = NULL;
	i = 0;
	input_btw_pipe = parse_pipe(input);
	if (!input_btw_pipe)
	{
		error(NL, 2, NULL, NULL);
		return (NULL);
	}
	while (input_btw_pipe[i])
	{
		c = create_cmdlist(input_btw_pipe[i], c, d);
		if (!c)
		{
			ft_freetab(input_btw_pipe);
			return (NULL);
		}
		i++;
	}
	ft_freetab(input_btw_pipe);
	return (c);
}

t_data	init_term(char **av, char **envp)
{
	t_data	d;

	d.input = NULL;
	d.env = ft_tabdup(envp);
	if (!d.env)
		malloc_error();
	d = init_vars(d, av, NULL, NULL);
	d = init_pwd(d);
	return (d);
}
