/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:57:39 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/24 21:34:37 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_shell *shell, t_cmd *curr, int i, int heredoc_num)
{
	t_cmd	*head;

	head = curr;
	while (head && heredoc_num <= 16)
	{
		if (head->type == HereDoc)
			heredoc_num++;
		head = head->next;
	}
	if (heredoc_num > 16)
		ft_putstr_fd("minishell: maximum here-doc count exceeded\n", 2);
	if (heredoc_num > 16)
		exit_minishell(shell->mem, 2);
	while (curr && i != 130)
	{
		if (curr->type == HereDocDel)
		{
			if (ft_strcmp(curr->arg[0], "\'\'") == 0
				|| ft_strcmp(curr->arg[0], "\"\"") == 0)
				curr->arg[0] = msh_strdup("", shell->mem);
			i = open_heredoc(shell, curr, 0, 0);
		}
		curr = curr->next;
	}
	return (i);
}

static int	check_for_pipe(t_cmd *cmd)
{
	if (!cmd->prev || cmd->prev->type == None)
	{
		if (cmd->next && cmd->next->type == Pipe)
			return (error_msg_v1("||"));
		return (error_msg_v1("|"));
	}
	else if (cmd->prev->type != Pipe)
	{
		if (cmd->next && cmd->next->type == Pipe)
			return (error_msg_v1("||"));
		else if (!cmd->next || (cmd->next && cmd->next->type == None
				&&!cmd->next->next))
			return (error_msg_v1("newline"));
	}
	return (0);
}

static int	check_for_in_out_put(t_cmd *cmd)
{
	if (!cmd->next || (cmd->next->type == None && !cmd->next->next))
		return (error_msg_v1("newline"));
	else if (cmd->next && cmd->next->next && cmd->next->type == Pipe
		&& cmd->next->next->type == Pipe)
		return (error_msg_v2(cmd->next->arg[0]));
	else if (cmd->next && cmd->next->op_type == Operation)
		return (error_msg_v1(cmd->next->arg[0]));
	else if (cmd->prev && cmd->prev->type == None && cmd->prev->prev
		&& cmd->prev->prev->type != Pipe)
		return (error_msg_v1(cmd->arg[0]));
	return (0);
}

static int	check_for_append_heredoc(t_cmd *cmd)
{
	if (!cmd->next || (cmd->next->type == None && !cmd->next->next))
		return (error_msg_v1("newline"));
	else if (cmd->prev && cmd->prev->type == None && cmd->prev->prev
		&& cmd->prev->prev->type != Pipe)
		return (error_msg_v1(cmd->next->arg[0]));
	else if (cmd->next && cmd->next->op_type == Operation)
		return (error_msg_v1(cmd->next->arg[0]));
	else if (cmd->next && cmd->next->next && cmd->next->type == Pipe
		&& cmd->next->next->type == Pipe)
		return (error_msg_v2(cmd->next->arg[0]));
	else if (cmd->next && cmd->next->op_type == Operation)
		return (error_msg_v1(cmd->next->arg[0]));
	else if (cmd->next && cmd->next->type == None && cmd->next->next
		&& (cmd->next->next->type == Append || cmd->next->next->type == 10))
		return (error_msg_v1(cmd->next->next->arg[0]));
	return (0);
}

int	error_management(t_shell *shell, int i)
{
	t_cmd	*curr;

	curr = shell->cmd_list;
	i = heredoc(shell, curr, i, 0);
	while (curr && i == 0)
	{
		if (curr->type == Pipe)
			i = check_for_pipe(curr);
		else if (curr->type == Output || curr->type == Input)
			i = check_for_in_out_put(curr);
		else if (curr->type == Append || curr->type == HereDoc)
			i = check_for_append_heredoc(curr);
		curr = curr->next;
	}
	return (i);
}
