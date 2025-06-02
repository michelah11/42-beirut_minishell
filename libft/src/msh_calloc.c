/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_calloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 00:25:27 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/01/13 03:14:16 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	s_zero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	*msh_calloc(size_t nmemb, size_t size, t_mem *mem)
{
	void	*ptr;

	if (nmemb && size && nmemb > (2000000000 / size))
		return (NULL);
	ptr = (void *)msh_malloc(nmemb * size, mem);
	if (!ptr)
		return (NULL);
	s_zero(ptr, nmemb * size);
	return (ptr);
}
