/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:54:58 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/08 19:32:15 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_list(t_shell *shell, int size)
{
	t_cmd	*node;
	t_cmd	*last;
	int		i;

	if (!shell->commands && !*shell->commands)
	{
		shell->cmd_list = lstnew(shell->mem, "\n", NULL, NULL);
		return ;
	}
	i = 0;
	shell->cmd_list = lstnew(shell->mem, shell->commands[i++], NULL, NULL);
	if (!shell->cmd_list)
		return ;
	last = shell->cmd_list;
	while (i < size)
	{
		node = lstnew(shell->mem, shell->commands[i], shell->cmd_list, NULL);
		if (!node)
			return ;
		last->next = node;
		node->prev = last;
		last = node;
		i++;
	}
}
