/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmdlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:33:08 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/16 21:37:17 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_last_cmd(t_cmd *c)
{
	t_cmd	*ptr;

	ptr = c;
	while (ptr && ptr->next)
		ptr = ptr->next;
	return (ptr);
}

static t_cmd	*new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		malloc_error();
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->in = STDIN_FILENO;
	new_cmd->out = STDOUT_FILENO;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

static t_cmd	*add_cmd(t_cmd *first)
{
	t_cmd	*new;

	new = first;
	while (new && new->next)
		new = new->next;
	new->next = new_cmd();
	if (!new->next)
		malloc_error();
	new->next->prev = new;
	new->next->next = NULL;
	return (first);
}

static t_cmd	*fill_cmd(char **input, t_cmd *first, t_data *d)
{
	int		i;
	t_cmd	*ptr;

	ptr = get_last_cmd(first);
	ptr->full_cmd = dup_fullcmd(input);
	ptr->path = ft_getpaths(d->env, ptr->full_cmd[0]);
	if (ptr->path)
		d->env = set_env_var("_", ptr->path, d, 1);
	else
	{
		i = 0;
		while (ptr->full_cmd[i] && ptr->full_cmd[i + 1])
			i++;
		d->env = set_env_var("_", ptr->full_cmd[i], d, 1);
	}
	return (first);
}

t_cmd	*create_cmdlist(char *input_split, t_cmd *c, t_data *d)
{
	char	**parsed_input;

	if (!c)
		c = new_cmd();
	else
		c = add_cmd(c);
	if (!c)
		malloc_error();
	c = redirection(c, NULL, input_split, d->env);
	if (!c)
		return (NULL);
	parsed_input = parse_cmd(input_split, d->env);
	if (!parsed_input)
	{
		free_cmd(c);
		return (NULL);
	}
	c = fill_cmd(parsed_input, c, d);
	if (!c)
		malloc_error();
	ft_freetab(parsed_input);
	return (c);
}
