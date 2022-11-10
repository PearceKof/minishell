/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:33:08 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/10 18:18:37 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_cmd(const char *src)
{
	char	*mem;
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (src[i] != '\0')
	{
		if (src[i++] != ' ')
			size++;
	}
	if (size == 0)
		return (NULL);
	mem = malloc((size + 1) * sizeof(char));
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		mem[i] = src[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

char	**dup_fullcmd(char **tab)
{
	char	**tabdup;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (tab[i])
	{
		if (!ft_strchr(tab[i], ' '))
			size++;
		i++;
	}
	tabdup = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tabdup)
		return (NULL);
	tabdup[size] = NULL;
	i = 0;
	size = 0;
	while (tab[i])
	{
	printf("DEBUG 3\n");
		if (!ft_strchr(tab[i], ' '))
			tabdup[size++] = dup_cmd(tab[i]);
		if (!tabdup[size - 1] && tab[i])
		{
			while (--size)
				free(tabdup[size]);
			free(tabdup);
			return (NULL);
		}
		i++;
		printf("DEBUG 4\n");
	}
	return (tabdup);
}

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
	size_t	i;
	size_t	j;

	ptr = first;
	while (ptr->next)
		ptr = ptr->next;
	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == '<' || input[i][j] == '>')
				redirection(input, ptr, i, j);
			j++;
		}
		i++;
	}
	ptr->full_cmd = dup_fullcmd(input);
	// ptr->full_cmd = ft_tabdup(input);
	return (first);
}

t_cmd	*init_cmd(char *input)
{
	char	**input_split;
	char	**nospace_input;
	t_cmd	*c;
	size_t	i;

	c = NULL;
	input_split = ft_split(input, '|');
	i = 0;
	while (input_split[i])
	{
		if (!c)
			c = new_cmd();
		else
			c = add_cmd(c);
		nospace_input = split_cmd(input_split[i]);
		if (!nospace_input)
			return (free_cmd(c));
		c = fill_cmd(nospace_input, c);
		ft_freetab(nospace_input);
		i++;
	}
	return (c);
}
