/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:27:27 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/25 22:18:20 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_is_in(char *str)
{
	int		i;
	int		count;
	int		in_single_quote;

	i = 0;
	count = 0;
	in_single_quote = 0;
	while (str[i])
	{
		if ((!in_single_quote && str[i] == 39 && check_ex(str, i))
			|| (str[i] == 39 && in_single_quote))
			in_single_quote = !in_single_quote;
		if (!in_single_quote && str[i] == '$' && str[i + 1]
			&& str[i + 1] != '$')
			count++;
		else if (str[i] == '$' && (str[i + 1] == '$'))
			i++;
		i++;
	}
	return (count);
}

int	check_ex(char *str, int size)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (!size)
		return (true);
	while (str[i] && i < size)
	{
		if (str[i] == 34)
			flag++;
		i++;
	}
	if (!(flag % 2))
		return (1);
	return (0);
}
