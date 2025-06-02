/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:33:55 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/08 19:18:35 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token1(t_cmd *cmd, char c)
{
	if (c == '<')
	{
		if (cmd->prev && cmd->prev->type == None)
			cmd->prev->type = Cmd;
		if (cmd->next && cmd->next->type == None)
			cmd->next->type = Infile;
		cmd->type = Input;
	}
	else if (c == '>')
	{
		if (cmd->prev && cmd->prev->type == None)
			cmd->prev->type = Cmd;
		if (cmd->next && cmd->next->type == None)
			cmd->next->type = Outfile;
		cmd->type = Output;
	}
	else if (c == '|')
	{
		if (cmd->prev && cmd->prev->type == None)
			cmd->prev->type = Cmd;
		if (cmd->next && cmd->next->type == None)
			cmd->next->type = Cmd;
		cmd->type = Pipe;
	}
}

static void	token2(t_cmd *cmd, int i)
{
	if (i == 1)
	{
		if (cmd->prev && cmd->prev->type == None)
			cmd->prev->type = Cmd;
		if (cmd->next && cmd->next->type == None)
			cmd->next->type = AppendFile;
		cmd->type = Append;
	}
	else if (i == 2)
	{
		if (cmd->prev && cmd->prev->type == None)
			cmd->prev->type = Cmd;
		if (cmd->next && cmd->next->type == None)
			cmd->next->type = HereDocDel;
		cmd->type = HereDoc;
	}
}

void	non_token(t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->arg[0])
			cmd->type = None;
		if (cmd->type == None && cmd->prev && cmd->prev->type == Outfile)
			cmd->type = Cmd;
		if (cmd->type == Input || cmd->type == Output || cmd->type == Append
			|| cmd->type == HereDoc || cmd->type == Pipe)
			cmd->op_type = Operation;
		else
			cmd->op_type = NonOperation;
		cmd = cmd->next;
	}
}

void	init_tokens(t_cmd *cmd, int size, t_cmd *list)
{
	while (cmd)
	{
		size = ft_strlen(cmd->arg[0]);
		if (size == 1 && cmd->arg[0][0] == '<')
			token1(cmd, '<');
		else if (size == 1 && cmd->arg[0][0] == '>')
			token1(cmd, '>');
		else if (size == 1 && cmd->arg[0][0] == '|')
			token1(cmd, '|');
		else if (size == 2 && cmd->arg[0][0] == '>' && cmd->arg[0][1] == '>')
			token2(cmd, 1);
		else if (size == 2 && cmd->arg[0][0] == '<' && cmd->arg[0][1] == '<')
			token2(cmd, 2);
		else if (!cmd->prev && !cmd->next)
			cmd->type = Cmd;
		else if (cmd->type == None && cmd->prev
			&& (cmd->prev->type == Outfile || cmd->prev->type == Infile
				|| cmd->prev->type == Append
				|| cmd->prev->type == HereDocDel))
			cmd->type = Cmd;
		if (cmd)
			cmd = cmd->next;
	}
	non_token(list);
}
