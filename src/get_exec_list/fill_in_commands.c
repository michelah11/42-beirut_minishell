/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:31:39 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/26 23:56:28 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_command_char(t_mem *mem, char **str)
{
	char	**ptr;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ptr = msh_malloc(sizeof(char *) * (array_size(str) + 1), mem);
	i = 0;
	while (str[i])
	{
		ptr[i] = msh_strdup(str[i], mem);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

void	fill_in_commands(t_shell *sh, t_exc **c, t_file **inf, t_file **outf)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	if (cmd->arg && !(*c)->cmd && (cmd->type == Cmd || cmd->type == None))
		(*c)->cmd = copy_command_char(sh->mem, cmd->arg);
	else if (cmd->arg && cmd->type == Infile)
	{
		if (!(*inf))
			(*inf) = new_node(sh->mem, *inf, cmd->arg[0], cmd->type);
		else
		{
			(*inf) = new_node(sh->mem, *inf, cmd->arg[0], cmd->type);
			// *inf = (*inf)->next;
		}
	}
	else if (cmd->arg && (cmd->type == Outfile || cmd->type == AppendFile))
	{
		if (!(*outf))
			(*outf) = new_node(sh->mem, *outf, cmd->arg[0], cmd->type);
		else
		{
			(*outf) = new_node(sh->mem, *outf, cmd->arg[0], cmd->type);
			// *outf = (*outf)->next;
		}
	}
}
