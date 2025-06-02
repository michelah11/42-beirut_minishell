/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 04:41:49 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/01/11 17:11:01 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotation(char *str)
{
	char	c;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			c = str[i];
			while (str[++i])
			{
				if (str[i] == c)
					break ;
			}
			if (str[i] == '\0')
			{
				error_msg_v1("newline");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
