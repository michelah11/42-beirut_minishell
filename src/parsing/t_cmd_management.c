/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:50:45 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/08 19:54:41 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstclear(t_cmd **list)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		free_array(current->arg);
		free(current);
		current = next;
	}
	*list = NULL;
}

t_cmd	*lstlast(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_cmd	*lstnew(t_mem *mem, char *cmd, t_cmd *list, char **str)
{
	t_cmd	*n_node;
	t_cmd	*last_node;

	n_node = (t_cmd *)msh_malloc(sizeof(struct s_cmd), mem);
	if (!n_node)
		return (NULL);
	if (cmd)
		n_node->arg = msh_split(cmd, ' ', mem);
	else
		n_node->arg = str;
	n_node->type = None;
	n_node->next = NULL;
	n_node->prev = NULL;
	if (list)
	{
		last_node = lstlast(list);
		if (last_node)
		{
			last_node->next = n_node;
			n_node->prev = last_node;
		}
	}
	return (n_node);
}
