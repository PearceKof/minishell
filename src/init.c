/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:29 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/07 22:29:23 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_getpid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (!pid)
		exit(1);
	waitpid(pid, NULL, 0);
	return (pid - 1);
}

static t_data	init_vars(t_data d, char *str, char **av)
{
	char	*tmp;

	str = ft_getenv("SHLVL", d.env, 5);
	if (!str || ft_atoi(str) <= 0)
		tmp = ft_strdup("1");
	else
		tmp = ft_itoa(ft_atoi(str) + 1);
	// free(str);
	d.env = set_env_var("SHLVL", tmp, &d, 5);
	free(tmp);
	tmp = getcwd(NULL, 0);
	d.env = set_env_var("PWD", tmp, &d, 3);
	free(tmp);
	if (!ft_getenv("PATH", d.env, 4))
		d.env = set_env_var("PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", &d, 4);
	if (!ft_getenv("_", d.env, 1))
		d.env = set_env_var("_", av[0], &d, 1);
	return (d);
}

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

t_data	init_term(char **av, char **envp, t_data d)
{
	char		*str;

	str = NULL;
	d.input = NULL;
	d.env = ft_tabdup(envp);
	d.pid = ft_getpid();
	d = init_vars(d, str, av);
	return (d);
}
/*
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
	d->input = NULL;
	d->env = ft_tabdup(envp);
	d->env = init_env(av, d);
	if (!d->env)
		exit(EXIT_FAILURE);
	return (d);
}
*/