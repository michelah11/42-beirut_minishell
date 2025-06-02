/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:13:27 by tayoub            #+#    #+#             */
/*   Updated: 2025/02/23 01:14:45 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_n_flag(char *str)
{
	str++;
	while (str && *str)
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

void	msh_echo(char **com, bool flag, int i)
{
	if (!com[0])
		ft_putstr_fd("\n", 1);
	if (!com[0])
		return ;
	if (com[0][0] == '-' && com [0][1] == 'n')
	{
		while (com[0] && com[0][0] == '-')
		{
			if (check_n_flag(com[0]) == true)
			{
				flag = false;
				com++;
			}
			else
				break ;
		}
	}
	while (com[i])
	{
		ft_putstr_fd(com[i++], 1);
		if (com[i])
			ft_putchar_fd(' ', 1);
	}
	if (flag == true)
		ft_putstr_fd("\n", 1);
}
