/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_spc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayoub <tayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:07:38 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/22 20:32:46 by tayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmdcheck(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*rm_spaces(t_mem *mem, char *str, int i)
{
	int		k;
	int		l;
	char	*ptr;

	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	l = i;
	k = i;
	if (str && str[k] == '\0')
		return (NULL);
	while (str[i++])
		l++;
	i--;
	while (str && (str[i] == ' ' || str[i] == '\t'))
	{
		i--;
		l--;
	}
	ptr = msh_malloc(sizeof(char) * (l - k + 1), mem);
	i = 0;
	while (k < l)
		ptr[i++] = str[k++];
	ptr[i] = '\0';
	return (ptr);
}
