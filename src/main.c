/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:47:18 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/17 11:43:26 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

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

static	int	is_correct_input(char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (is_only_space(input) || input[0] == '\0')
		return (0);
	add_history(input);
	if (is_invalid_syntax(input))
		return (0);
	return (1);
}

void	prompt(t_data *d)
{
	char	*prompt;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		prompt = ft_strjoin(pwd, "=> ");
		if (!prompt)
			malloc_error();
		d->input = readline(prompt);
		free(prompt);
		free(pwd);
	}
	else
		d->input = readline("=> ");
}

int	main(int ac, char **av, char **envp)
{
	t_data	d;
	t_cmd	*c;

	d = init_term(av, envp, d);
	g_status = 0;
	while (ac && av)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		prompt(&d);
		if (is_correct_input(d.input))
		{
			c = init_cmd(d.input, &d);
			if (c)
			{
				execute(c, &d);
			}
			free_cmd(c);
		}
		if (d.input)
			free(d.input);
	}
}
