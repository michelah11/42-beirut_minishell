/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:12:39 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/01/15 21:25:29 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*msh_malloc(size_t size, t_mem *node)
{
	void	*block;

	block = malloc(size);
	if (!block)
	{
		delete_list(node);
		exit(EXIT_FAILURE);
	}
	node = insert_node(node, block);
	return (block);
}
