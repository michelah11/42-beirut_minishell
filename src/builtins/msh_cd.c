/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:01:10 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 02:28:01 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_directory(t_shell *shell, char *path)
{
	char	*current;
	char	buffer[PATH_MAX];

	current = find_env_var(shell->env_list, "PWD");
	if (!path)
		return ;
	if (chdir(path) != 0)
	{
		perror("cd");
		g_sig.ret_code = 1;
	}
	else
	{
		set_env_after_cd(shell, "OLDPWD", current);
		set_env_after_cd(shell, "PWD", getcwd(buffer, PATH_MAX));
	}
}

static int	count_arguments(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	msh_cd(t_shell *shell, char **com)
{
	char	*home;
	int		c;

	c = count_arguments(com);
	if (c > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_sig.ret_code = 1;
		return ;
	}
	home = find_env_var(shell->env_list, "HOME");
	if (com[1] == NULL || (com[1][0] == '~' && com[1][1] == '\0'))
	{
		if (!home)
		{
			home = find_env_var(shell->env_list, "USER");
			home = ft_strjoin("/home/", home);
		}
		change_directory(shell, home);
	}
	else
		change_directory(shell, com[1]);
}
