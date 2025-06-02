/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 01:26:18 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/02/23 00:38:11 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_env(t_env *env_list)
{
	int		i;
	bool	flag;

	while (env_list)
	{
		i = 0;
		flag = false;
		while (env_list->var_name[i])
		{
			if (env_list->var_name[i] == '=')
			{
				flag = true;
				break ;
			}
			i++;
		}
		if (flag == true)
		{
			ft_putstr_fd(env_list->var_name, 1);
			ft_putchar_fd('\n', 1);
		}
		env_list = env_list->next;
	}
}
