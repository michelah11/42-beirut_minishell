/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_strmapi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 00:51:17 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/01/13 02:18:05 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*msh_strmapi(char const *s, char (*f)(unsigned int, char), t_mem *mem)
{
	char			*str;
	unsigned int	i;

	if (!f || !s)
		return (NULL);
	str = (char *)msh_malloc(sizeof(char) * (ft_strlen(s) + 1), mem);
	if (!str)
		return (NULL);
	i = 0;
	if (f && s)
	{
		while (s[i] != '\0')
		{
			str[i] = (*f)(i, s[i]);
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
