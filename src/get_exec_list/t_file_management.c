/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:43:31 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/02/10 20:58:31 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_list_clear(t_file **list)
{
	t_file	*current;
	t_file	*next;

	if (!list || !*list)
		return ;
	current = *list;
	while (current->next)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
	*list = NULL;
}

t_file	*last_file_node(t_file *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_file	*new_node(t_mem *mem, t_file *list, char *str, t_token type)
{
	t_file	*node;
	t_file	*last_node;

	node = (t_file *)msh_malloc(sizeof(struct s_file), mem);
	if (!node)
		return (NULL);
	node->file = str;
	node->file_type = type;
	node->next = NULL;
	if (!list)
		node->prev = NULL;
	else
	{
		last_node = last_file_node(list);
		node->prev = last_node;
		last_node->next = node;
	}
	return (node);
}
