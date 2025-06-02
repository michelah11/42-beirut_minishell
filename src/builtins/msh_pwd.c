/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:25:47 by tayoub            #+#    #+#             */
/*   Updated: 2025/04/03 02:28:15 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_pwd(t_env *env_list)
{
	char	buffer[PATH_MAX];
	char	*curr_dir;
	char	*path;

	curr_dir = getcwd(buffer, PATH_MAX);
	if (curr_dir)
	{
		ft_putstr_fd(curr_dir, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		path = find_env_var(env_list, "PWD");
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
	}
}
