/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:15:43 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/04 21:10:39 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	delete_list(t_mem *node)
{
	t_mem	*current;

	while (node)
	{
		current = node->next;
		if (node->address)
		{
			free(node->address);
			node->address = NULL;
		}
		free(node);
		node = current;
	}
}
