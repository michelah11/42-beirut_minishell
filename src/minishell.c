/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 09:36:08 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/27 00:24:29 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

int	data_init(char **argv, t_shell *shell, char **env)
{
	(void)argv;
	g_sig.ret_code = 0;
	g_sig.flag = 0;
	dup_env(shell, env);
	return (1);
}

t_shell	*init_minishell(void)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env_list = NULL;
	shell->env_var = NULL;
	shell->mem = insert_node(NULL, shell);
	shell->hd = 0;
	return (shell);
}

static void	read_input(t_shell *shell)
{
	char	*tmp;

	tmp = ft_strdup("");
	shell->env_var = linked_list_to_array(shell);
	while (*tmp == '\0')
	{
		free (tmp);
		tmp = readline("minishell$ ");
		if (!tmp)
		{
			printf("exit\n");
			exit_minishell(shell->mem, g_sig.ret_code);
		}
	}
	shell->input_line = msh_strdup(tmp, shell->mem);
	free(tmp);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*minishell;

	minishell = init_minishell();
	if (!minishell)
		return (1);
	if (argc != 1 || !data_init(argv, minishell, env))
		return (1);
	while (1)
	{
		signal_handler();
		read_input(minishell);
		if (check_quotation(minishell->input_line))
		{
			add_history(minishell->input_line);
			pars_ln(minishell, 0);
		}
	}
}
