/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayoub <tayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:54:03 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 21:25:05 by tayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_one(char **com, t_exc *command, t_shell *shell,
		char *path)
{
	int	red;

	red = 0;
	signal(SIGINT, SIG_DFL);
	if (command->infile || command->outfile)
		red = handle_redirection(shell->mem, command);
	if (red == 1)
		exit_minishell_fd(shell, command, 1);
	else if (path == NULL && check_bi(com) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		if (((com[0][0] == 39 && com[0][1] == 39) || (com[0][0] == 34
				&& com[0][1] == 34)) && com[0][2] == '\0')
			ft_putstr_fd("'': command not found\n", 2);
		else if (check_bi(com) == 8)
			exit_minishell_fd(shell, command, errno);
		else
			msh_puterror(com[0], ": command not found\n");
		exit_minishell_fd(shell, command, errno);
	}
}

void	exec_cmd_two(t_exc *cmd, t_shell *shell)
{
	if (cmd->prev && !cmd ->infile)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		msh_close(shell->fd_in, "fd_in\n");
	}
	if (cmd->next && !cmd->outfile)
	{
		dup2(shell->fd[1], STDOUT_FILENO);
	}
	if (cmd->next)
	{
		msh_close(shell->fd[1], "child fd[0]\n");
		msh_close(shell->fd[0], "child fd[1]\n");
	}
}

void	exec_cmd_three(char **com, t_exc *c, t_shell *shell, char *path)
{
	struct stat	stats;
	int			cmd;

	cmd = check_bi(com);
	if (cmd == 0)
	{
		if (signal(SIGQUIT, print_signals_c) != SIG_ERR)
			g_sig.ret_code = 131;
		execve(path, com, shell->env_var);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(com[0], 2);
		ft_putstr_fd(": ", 2);
		stat(path, &stats);
		if (S_ISDIR(stats.st_mode))
			ft_putendl_fd("Is a directory", 2);
		else
			ft_putendl_fd(strerror(errno), 2);
		exit_minishell(shell->mem, -1);
	}
	else
		run_builtins(shell, c, cmd, 1);
}
