/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayoub <tayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 01:30:18 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 21:14:59 by tayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*update_shlvl(t_mem *mem, char *env, int subshell)
{
	char	**shlvl_arr;
	char	*str;

	shlvl_arr = ft_split(env, '=');
	if (!shlvl_arr)
		return (NULL);
	subshell = ft_atoi(shlvl_arr[1]);
	str = msh_itoa(++subshell, mem);
	if (!str)
	{
		free_array(shlvl_arr);
		return (NULL);
	}
	free_array(shlvl_arr);
	return (str);
}

void	creat_env_list(t_shell *shell, char **env, int subshell, int i)
{
	char	*str;
	t_env	*node;
	t_env	*current_node;

	shell->env_list = env_new(shell->mem, shell->env_list,
			msh_strdup(env[i++], shell->mem));
	while (env[i])
	{
		if (ft_strncmp("SHLVL", env[i], 5) == 0)
		{
			str = update_shlvl(shell->mem, env[i++], subshell);
			if (str)
			{
				node = env_new(shell->mem, shell->env_list, msh_strjoin("SHLVL",
							msh_strjoin("=", str, shell->mem), shell->mem));
			}
		}
		else
			node = env_new(shell->mem, shell->env_list,
					msh_strdup(env[i++], shell->mem));
		current_node = env_last(shell->env_list);
		if (current_node)
			current_node->next = node;
	}
}

void	dup_env(t_shell *shell, char **env)
{
	shell->env_list = NULL;
	if (!env[0])
	{
		env = creat_myenv(shell->mem);
		creat_env_list(shell, env, 0, 0);
	}
	else
		creat_env_list(shell, env, 0, 0);
}
