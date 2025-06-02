/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exc_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:34:49 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/02/10 01:43:07 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commands_clear(t_exc **list)
{
	t_exc	*current;
	t_exc	*next;

	if (!list || !(*list))
		return ;
	current = *list;
	while (current->next)
	{
		next = current->next;
		free_array(current->cmd);
		file_list_clear(&current->infile);
		file_list_clear(&current->outfile);
		free(current);
		current = next;
	}
	free_array(current->cmd);
	file_list_clear(&current->infile);
	file_list_clear(&current->outfile);
	free(current);
	*list = NULL;
}

t_exc	*command_last(t_exc *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_exc	*command_new(t_mem *mem, t_exc *list)
{
	t_exc	*n_node;
	t_exc	*last_node;

	n_node = (t_exc *)msh_malloc(sizeof(struct s_exc), mem);
	if (!n_node)
		return (NULL);
	n_node->cmd = NULL;
	n_node->infile = NULL;
	n_node->outfile = NULL;
	n_node->next = NULL;
	if (!list)
		n_node->prev = NULL;
	else
	{
		last_node = command_last(list);
		n_node->prev = last_node;
		last_node->next = n_node;
	}
	return (n_node);
}

int	get_command_size(t_exc *cmd)
{
	int	size;

	size = 0;
	while (cmd)
	{
		cmd = cmd->next;
		size++;
	}
	return (size);
}
