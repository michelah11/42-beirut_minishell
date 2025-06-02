/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:09:43 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/01/14 23:02:01 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_vars(t_mem *mem, char **vars)
{
	char	*line;
	int		i;
	int		j;
	int		size;

	i = 0;
	size = 0;
	j = 0;
	while (vars[i])
		size += ft_strlen(vars[i++]);
	line = msh_malloc(sizeof(char) * (size + 1), mem);
	i = 0;
	size = 0;
	while (vars[i])
	{
		j = 0;
		while (vars[i][j])
			line[size++] = vars[i][j++];
		i++;
	}
	line[size] = '\0';
	return (line);
}
