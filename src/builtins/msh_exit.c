/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:47:45 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/30 01:44:43 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_digit_char(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-' && *str != '+')
			return (0);
		str++;
	}
	return (1);
}

static void	error_arg_print(t_mem *mem, char *nstr)
{
	printf("minihsell: ");
	printf("%s: ", nstr);
	printf("numeric argument required\n");
	msh_close(STDIN_FILENO, "IN");
	msh_close(STDOUT_FILENO, "OUT");
	exit_minishell(mem, 2);
}

static void	lltoi(t_mem *mem, long long int i, char *nstr)
{
	if (((nstr[0] == '-' || nstr[0] == '+') && ft_strlen(nstr) > 20)
		|| (ft_isdigit(nstr[0]) && ft_strlen(nstr) > 19))
		error_arg_print(mem, nstr);
	else if (ft_strlen(nstr) == 19 && ft_isdigit(nstr[0]))
	{
		if (ft_strcmp(nstr, "9223372036854775807") > 0)
			error_arg_print(mem, nstr);
	}
	else if (ft_strlen(nstr) == 20)
	{
		if (ft_strcmp((nstr + 1), "9223372036854775807") > 0 && nstr[0] == '+')
			error_arg_print(mem, nstr);
		else if (ft_strcmp((nstr + 1), "9223372036854775808") > 0
			&& nstr[0] == '-')
			error_arg_print(mem, nstr);
	}
	i = msh_atoi(nstr);
	i %= 256;
	if (i < 0)
		i += 256;
	g_sig.ret_code = (int)i;
	msh_close(STDIN_FILENO, "IN");
	msh_close(STDOUT_FILENO, "OUT");
	exit_minishell(mem, (int)i);
}

static void	child_exit(t_mem *mem, char **com)
{
	if (!com[1])
		exit_minishell(mem, g_sig.exit_code);
	else if (!is_digit_char(com[1]))
		error_arg_print(mem, com[1]);
	else if (com[1] && com[2])
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else
		lltoi(mem, 0, com[1]);
}

void	msh_exit(t_mem *mem, char **com, int flag)
{
	if (flag != 0)
		child_exit(mem, com);
	else if (!com[1])
	{
		printf("exit\n");
		msh_close(STDIN_FILENO, "IN");
		msh_close(STDOUT_FILENO, "OUT");
		exit_minishell(mem, g_sig.exit_code);
	}
	else if (!is_digit_char(com[1]))
		error_arg_print(mem, com[1]);
	else if (com[1] && com[2])
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else
		lltoi(mem, 0, com[1]);
}
