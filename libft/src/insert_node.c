/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:17:06 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/01/13 03:18:59 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mem	*insert_node(t_mem *node, void *value)
{
	t_mem	*new_node;
	t_mem	*head;

	new_node = (t_mem *)malloc(sizeof(t_mem));
	if (!new_node)
		return (NULL);
	new_node->address = value;
	new_node->next = NULL;
	if (!node)
		return (new_node);
	head = node;
	while (node->next)
		node = node->next;
	node->next = new_node;
	return (head);
}
