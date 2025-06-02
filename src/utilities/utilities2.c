/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:24:22 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/27 23:33:00 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_close(int fd, char *str)
{
	int	n;

	n = close(fd);
	if (n == -1)
		printf("Right here %s\n", str);
}

int	msh_fork(t_mem *mem)
{
	int	n;

	n = fork();
	if (n == -1)
		exit_minishell(mem, 1);
	return (n);
}

void	msh_clear(t_shell *shell)
{
	lstclear(&shell->cmd_list);
	free_array(shell->commands);
}
