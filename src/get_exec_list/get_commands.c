/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:40:13 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/02/11 00:17:33 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exc	*get_command(t_mem *mem, t_cmd *list)
{
	t_exc		*node;
	t_exc		*head;
	t_cmd		*l;

	node = command_new(mem, NULL);
	head = node;
	l = list;
	while (l)
	{
		if (l->type == Pipe)
			node = command_new(mem, node);
		l = l->next;
	}
	return (head);
}

static t_file	*get_head(t_file *list)
{
	while (list)
	{
		if (!list->prev)
			break ;
		list = list->prev;
	}
	return (list);
}

t_exc	*get_commands(t_shell *shell)
{
	t_exc		*command;
	t_exc		*head;
	t_file		*infile;
	t_file		*outfile;

	command = get_command(shell->mem, shell->cmd_list);
	head = command;
	while (command && shell->cmd_list)
	{
		infile = NULL;
		outfile = NULL;
		while (shell->cmd_list && shell->cmd_list->type != Pipe)
		{
			fill_in_commands(shell, &command, &infile, &outfile);
			shell->cmd_list = shell->cmd_list->next;
		}
		command->infile = get_head(infile);
		command->outfile = get_head(outfile);
		if (shell->cmd_list)
			shell->cmd_list = shell->cmd_list->next;
		command = command->next;
	}
	command = head;
	return (command);
}
