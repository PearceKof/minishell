/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmdlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:33:08 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/13 18:49:44 by blaurent         ###   ########.fr       */
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

static t_cmd	*fill_cmd(char **input, t_cmd *first)
{
	t_cmd	*ptr;

	ptr = get_last_cmd(first);
	ptr->full_cmd = dup_fullcmd(input);
	return (first);
}

t_cmd	*create_cmdlist(char *input_split, t_cmd *c, char **env, t_data *d)
{
	char	**parsed_input;
	(void)d;
	if (!c)
		c = new_cmd();
	else
		c = add_cmd(c);
	if (!c)
		malloc_error();
	c = redirection(c, NULL, input_split, env);
	if (!c)
		return (NULL);
	parsed_input = parse_cmd(input_split, env);
	c = fill_cmd(parsed_input, c);
	if (!c)
		malloc_error();
	ft_freetab(parsed_input);
	return (c);
}

