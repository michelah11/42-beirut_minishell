/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayoub <tayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:23:43 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 21:23:18 by tayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_pid(int *pid, int cmd_num)
{
	int	i;
	int	status;

	if (cmd_num == 0)
		return (0);
	i = cmd_num;
	status = 0;
	waitpid(pid[--i], &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	while (i >= 0)
		waitpid(pid[i--], 0, 0);
	if (g_sig.ret_code == 130)
		return (130);
	return (status);
}

static int	check(t_exc *list)
{
	if (list)
	{
		if (list->cmd && list->cmd[0] && !ft_strcmp(list->cmd[0], "cat")
			&& list->cmd[1] == NULL)
			return (1);
	}
	return (0);
}

static void	ex_pipes(t_shell *shell, t_exc *list, t_exc *lx)
{
	shell->proc_idx = 0;
	shell->pid = msh_malloc(sizeof(int) * (get_command_size(list)), shell->mem);
	shell->fd_in = STDIN_FILENO;
	while (list)
	{
		if (list->next)
		{
			if (pipe(shell->fd) == -1)
				break ;
		}
		g_sig.ret_code = execute_command(list, shell, shell->proc_idx++);
		if (g_sig.ret_code == 0 && shell->proc_idx != 0 && !check(lx))
			g_sig.ret_code = wait_pid(shell->pid, shell->proc_idx);
		if (shell->fd_in != STDIN_FILENO)
			msh_close(shell->fd_in, "parrent fd_in\n");
		if (list->next)
		{
			msh_close(shell->fd[1], "shell->fd[0]");
			shell->fd_in = shell->fd[0];
		}
		list = list->next;
	}
	if (shell->proc_idx != 0 && check(lx))
		g_sig.ret_code = wait_pid(shell->pid, shell->proc_idx);
	shell->pid = NULL;
}

int	ex_ln(t_shell *shell)
{
	t_exc	*list;
	int		builtins;

	list = shell->exec_list;
	builtins = check_bi(list->cmd);
	if (!list || (list->cmd && list->cmd[0][0] == '\n'))
		return (2);
	change_(shell, list, NULL, 0);
	if (builtins != 0 && !list->next)
		ex_builtins(shell, list, builtins);
	else
		ex_pipes(shell, list, shell->exec_list);
	g_sig.exit_code = g_sig.ret_code;
	return (g_sig.ret_code);
}
