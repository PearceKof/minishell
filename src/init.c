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

static void	ft_getpid(t_data *d)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (!pid)
		exit(1);
	waitpid(pid, NULL, 0);
	d->pid = pid - 1;
}

static t_data	init_vars(t_data d, char *str, char **av)
{
	char	*tmp;

	str = ft_getenv("SHLVL", d.env, 5);
	if (!str || ft_atoi(str) <= 0)
		tmp = ft_strdup("1");
	else
		tmp = ft_itoa(ft_atoi(str) + 1);
	free(str);
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

t_data	init_term(char **av, char **envp, t_data d)
{
	char		*str;

	str = NULL;
	d.input = NULL;
	d.env = ft_tabdup(envp);
	ft_getpid(&d);
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