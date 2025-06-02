/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayoub <tayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:00:53 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 21:21:32 by tayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_bi(char **str)
{
	int	c;

	c = 0;
	if (!str || !*str)
		return (c);
	if (ft_strcmp(str[0], "cd") == 0)
		c = 1;
	else if (ft_strcmp(str[0], "pwd") == 0)
		c = 2;
	else if (ft_strcmp(str[0], "env") == 0 && str[1] == NULL)
		c = 3;
	else if (ft_strcmp(str[0], "export") == 0)
		c = 4;
	else if (ft_strcmp(str[0], "unset") == 0)
		c = 5;
	else if (ft_strcmp(str[0], "exit") == 0)
		c = 6;
	else if (ft_strcmp(str[0], "echo") == 0)
		c = 7;
	else if (!ft_strcmp(str[0], ":") || !ft_strcmp(str[0], "!"))
		c = 8;
	return (c);
}

int	run_builtins(t_shell *shell, t_exc *cmd, int c, int flag)
{
	if (c == 1)
		msh_cd(shell, cmd->cmd);
	else if (c == 2)
		msh_pwd(shell->env_list);
	else if (c == 3)
		msh_env(shell->env_list);
	else if (c == 4)
		msh_export(shell, cmd->cmd, '-', 1);
	else if (c == 5)
		shell->env_list = msh_unset(shell->env_list, cmd->cmd, shell);
	else if (c == 6)
		msh_exit(shell->mem, cmd->cmd, flag);
	else if (c == 7)
		msh_echo(cmd->cmd + 1, true, 0);
	return (0);
}

void	ex_builtins(t_shell *shell, t_exc *list, int builtins)
{
	int	in;
	int	out;

	if (builtins != 6)
	{
		in = dup(STDIN_FILENO);
		out = dup(STDOUT_FILENO);
	}
	if (list->infile || list->outfile)
		g_sig.ret_code = handle_redirection(shell->mem, list);
	if (g_sig.ret_code != 1)
		run_builtins(shell, list, builtins, 0);
	if (g_sig.ret_code != 1 && list->infile)
		dup2(in, STDIN_FILENO);
	if (builtins != 6)
		msh_close(in, "in");
	if (g_sig.ret_code != 1 && list->outfile && builtins != 6)
	{
		dup2(out, STDOUT_FILENO);
		msh_close(out, "out");
	}
	else if (builtins != 6)
		msh_close(out, "out");
}
