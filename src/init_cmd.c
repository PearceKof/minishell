/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:33:08 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/21 15:45:14 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd()
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->in = STDIN_FILENO;
	new_cmd->out = STDOUT_FILENO;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*add_cmd(t_cmd *first)
{
	t_cmd	*new;

	new = first;
	while (new && new->next)
		new = new->next;
	new->next = new_cmd();
	if (!new->next)
		return (NULL);
	new->next->prev = new;
	new->next->next = NULL;
	return (first);
}

t_cmd	*fill_cmd(char **input, t_cmd *first)
{
	t_cmd	*ptr;
	// size_t	i;
	// size_t	j;

	ptr = first;
	while (ptr->next)
		ptr = ptr->next;
	// i = 0;
	// while (input[i])
	// {
	// 	j = 0;
	// 	while (input[i][j])
	// 	{
			// if (input[i][j] == '<' || input[i][j] == '>')
			// 	if (redirection(input, ptr, i, j))
			// 		return (NULL);
	// 		j++;
	// 	}
	// 	i++;
	// }
	ptr->full_cmd = dup_fullcmd(input);
	return (first);
}

static t_cmd	*create_cmdlist(char *input_split, t_cmd *c, char **env)
{
	char	**nospace_input;

	if (!c)
		c = new_cmd();
	else
		c = add_cmd(c);
	if (!c)
		exit(EXIT_FAILURE);
	nospace_input = split_cmd(input_split, env);
	if (!nospace_input)
		exit(EXIT_FAILURE);
	c = fill_cmd(nospace_input, c);
	ft_freetab(nospace_input);
	if (!c)
		exit(EXIT_FAILURE);
	return (c);
}

t_cmd	*init_cmd(char *input, char **env)
{
	char	**input_split;
	t_cmd	*c;
	size_t	i;

	c = NULL;
	i = 0;
	input_split = ft_split(input, '|');
	if (!input_split)
		exit(EXIT_FAILURE);
	while (input_split[i])
	{
		c = create_cmdlist(input_split[i], c, env);
		i++;
	}
	ft_freetab(input_split);
	return (c);
}
