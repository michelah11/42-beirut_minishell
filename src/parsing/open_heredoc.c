/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:15:28 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/27 00:33:38 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msh_strcmp_heredoc(t_mem *mem, char *s1, char *s2)
{
	char	*str;
	int		k;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str = get_string(msh_strdup(s2, mem), mem, 0, get_size(s2));
	while (s1[i] == str[i] && s1[i] != '\0' && str[i] != '\0')
		i++;
	k = s1[i] - str[i];
	return (k);
}

// static void	handle_sig(void)
// {
// 	static struct sigaction	sa;

// 	sa.sa_sigaction = signal_heredoc;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// }

static void	child(t_shell *shell, char *line, t_cmd *cmd, bool flag)
{
	int						k;
	int						fd;
	char					*tmp;

	fd = open(line, O_APPEND | O_CREAT | O_WRONLY, 0644);
	signal(SIGINT, signal_heredoc);
	line = readline(">");
	k = 1;
	while (1)
	{
		if (!line && print_error(shell->mem, k, cmd->arg[0]) == 0)
			break ;
		else if ((*cmd->arg[0] == '\0' && *line == '\0')
			|| msh_strcmp_heredoc(shell->mem, line, cmd->arg[0]) == 0)
			break ;
		k++;
		if (flag == true)
			tmp = expansion(line, shell);
		ft_putstr_fd(tmp, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline(">");
	}
	close(fd);
	exit_minishell(shell->mem, 0);
}

int	open_heredoc(t_shell *shell, t_cmd *cmd, int pid, int status)
{
	char	*line;
	bool	flag;

	flag = true;
	shell->hd = 1;
	check_quot_filename(shell->mem, &flag, &line, cmd->arg[0]);
	g_sig.flag = 1;
	pid = msh_fork(shell->mem);
	if (pid == 0)
		child(shell, line, cmd, flag);
	else if (pid < 0)
		ft_putstr_fd("minishell: fork fail while creating the Heredoc\n", 2);
	waitpid(pid, &status, 0);
	g_sig.flag = 0;
	cmd->arg[0] = line;
	cmd->prev->type = Input;
	cmd->type = Infile;
	if (status != 0)
		return (130);
	return (0);
}
