/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayoub <tayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 00:49:58 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/19 22:27:47 by tayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*msh_strjoin(char const *s1, char const *s2, t_mem *mem)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)msh_malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1),
			mem);
	if (!str)
		return (NULL);
	i = 0;
	j = 0 ;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
