/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:00:48 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/27 00:25:34 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion(char *input_line, t_shell *shell)
{
	char	**var;
	char	**splitted_line;
	char	*line;

	line = NULL;
	if (dollar_is_in(input_line))
	{
		var = get_vars(input_line, 0, 0);
		var = get_vars_content(input_line, var, shell, 0);
		splitted_line = msh_split_str(input_line, shell);
		if (!splitted_line)
			line = join_vars(shell->mem, var);
		else
			line = get_final_line(input_line, shell, splitted_line, var);
	}
	else
		return (input_line);
	return (line);
}

static char	*get_home(t_shell *shell)
{
	char	*home;

	home = find_env_var(shell->env_list, "HOME");
	{
		if (!home)
		{
			home = find_env_var(shell->env_list, "USER");
			home = msh_strjoin("/home/", home, shell->mem);
		}
	}
	return (home);
}

static void	check_madde(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;
	char	*home;

	home = get_home(shell);
	cmd = shell->cmd_list;
	while (cmd)
	{
		i = 0;
		while (cmd->arg && cmd->arg[i])
		{
			if (ft_strcmp(cmd->arg[i], "~") == 0)
				cmd->arg[i] = msh_strdup(home, shell->mem);
			if (cmd->arg[i][0] == '~' && cmd->arg[i][1] == '/')
				cmd->arg[i] = msh_strjoin(home, (cmd->arg[i] + 1), shell->mem);
			i++;
		}
		cmd = cmd->next;
	}
}

void	pars_ln(t_shell *shell, int i)
{
	char	*line;

	line = shell->input_line;
	line = expansion(line, shell);
	shell->input_line = line;
	shell->commands = msh_split_msh(shell);
	while (shell->commands[i])
	{
		if (!cmdcheck(shell->commands[i]))
			shell->commands[i] = rm_spaces(shell->mem, shell->commands[i], 0);
		i++;
	}
	get_list(shell, i);
	init_tokens(shell->cmd_list, 0, shell->cmd_list);
	g_sig.ret_code = error_management(shell, 0);
	if (g_sig.ret_code != 0)
		return ;
	check_madde(shell);
	remove_quotes(shell, shell->cmd_list);
	shell->exec_list = get_commands(shell);
	

	if (*(shell->exec_list->cmd) != NULL)
		g_sig.ret_code = ex_ln(shell);
	if (shell->hd == 1)
		unlink("/tmp/HereDoc");
}
