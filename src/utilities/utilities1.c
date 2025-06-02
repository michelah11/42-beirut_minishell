/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 01:27:47 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 01:20:31 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_mem *mem, int e)
{
	delete_list(mem);
	exit(e);
}

void	exit_minishell_fd(t_shell *shell, t_exc *cmd, int e)
{
	if (cmd->prev)
		msh_close(shell->fd_in, "fd_in");
	if (cmd->next)
	{
		msh_close(shell->fd[1], "fd[1]");
		msh_close(shell->fd[0], "fd[0]");
	}
	delete_list(shell->mem);
	exit(e);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	array_size(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
