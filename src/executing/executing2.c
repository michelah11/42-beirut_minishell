/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayoub <tayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:58:41 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 21:20:39 by tayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_(t_shell *sh, t_exc *cmd, char *arg, int i)
{
	t_env	*node;

	if (!cmd->cmd || !cmd->cmd[0])
		return ;
	while (cmd->next && cmd->next->cmd)
		cmd = cmd->next;
	while (cmd->cmd[i])
		i++;
	arg = cmd->cmd[--i];
	if (!arg || *arg == '\n')
		return ;
	node = find_env_var_index(sh->env_list, "_=");
	if (node)
		node->var_name = msh_strjoin("_=", arg, sh->mem);
	else
	{
		node = env_new(sh->mem, sh->env_list, msh_strjoin("_=", arg, sh->mem));
		sh->env_list = env_last(sh->env_list);
		if (sh->env_list)
			sh->env_list->next = node;
		else
			sh->env_list = node;
	}
	while (sh->env_list->prev)
		sh->env_list = sh->env_list->prev;
}

static char	*get_my_path(t_shell *shell, char **com, int i)
{
	char	**str;
	char	*path1;
	char	*mypath;
	char	*command_path;

	mypath = NULL;
	if (com[0][0] == '/' || com[0][0] == '.')
		return (msh_strdup(com[0], shell->mem));
	path1 = find_env_var(shell->env_list, "PATH");
	if (!path1)
		return (NULL);
	str = ft_split(path1, ':');
	while (str[i])
	{
		command_path = msh_strjoin(str[i], msh_strjoin("/", com[0], shell->mem),
				shell->mem);
		if (access(command_path, X_OK) == 0)
		{
			mypath = command_path;
			break ;
		}
		i++;
	}
	free_array(str);
	return (mypath);
}

int	execute_command(t_exc *command, t_shell *shell, int index)
{
	char	*path;

	if (!command->cmd)
		return (-1);
	if (command->cmd[0][0] == '\0' && !command->infile && !command->outfile)
		return (0);
	path = get_my_path(shell, command->cmd, 0);
	signal(SIGINT, SIG_IGN);
	shell->pid[index] = msh_fork(shell->mem);
	if (shell->pid[index] == 0)
	{
		exec_cmd_one(command->cmd, command, shell, path);
		exec_cmd_two(command, shell);
		if (command->cmd[0][0] != '\0')
			exec_cmd_three(command->cmd, command, shell, path);
		msh_close(STDIN_FILENO, "in");
		msh_close(STDOUT_FILENO, "out");
		exit_minishell(shell->mem, 0);
	}
	if (shell->pid[index] < 0)
		return (-1);
	return (0);
}
