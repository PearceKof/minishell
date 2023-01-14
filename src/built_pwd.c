/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:05:41 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/14 17:18:15 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_pwd(t_data *d)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_getenv("PWD", d->env, 3);
	new_pwd = getcwd(NULL, 0);
	set_env_var("OLDPWD", old_pwd, d, 6);
	set_env_var("PWD", new_pwd, d, 3);
	free(old_pwd);
	free(new_pwd);
}

int	ft_pwd(void)
{
	char	str[PATH_MAX];

	if ((getcwd(str, sizeof(str)) != NULL))
		printf("%s\n", str);
	return (1);
}
