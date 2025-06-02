/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:20:15 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/27 00:31:22 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_heredoc(int signum)
{
	printf("\nCaught signal %d. Exiting heredoc...\n", signum);
	exit_minishell(NULL, 130);
}

int	print_error(t_mem *mem, int k, char *str)
{
	char	*num;

	num = msh_itoa(k, mem);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(num, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("')\n", 2);
	return (0);
}

static int	count_quotes(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			i++;
		str++;
	}
	return (i);
}

void	check_quot_filename(t_mem *mem, bool *flag, char **filename, char *str)
{
	if (count_quotes(str) != 0)
		*flag = false;
	*filename = msh_strdup("/tmp/HereDoc", mem);
}
