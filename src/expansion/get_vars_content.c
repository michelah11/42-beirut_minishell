/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:52:48 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/25 22:30:58 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_back_for_heredoc(char *str, int index)
{
	if (index < 0 || !str[index])
		return (0);
	index--;
	while (index >= 0 && (str[index] == ' ' || str[index] == 9))
		index--;
	if (index >= 1 && str[index] == '<')
	{
		index--;
		if (index >= 0 && str[index] == '<')
			return (1);
	}
	return (0);
}

char	*get_content(t_shell *shell, char *str)
{
	int		i;
	int		size;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (!str)
		return (NULL);
	while (shell->env_var[i])
	{
		size = ft_strlen(str);
		ptr = ft_strnstr(shell->env_var[i], str, size);
		if (ptr)
		{
			if ((*(ptr + size) == '=') && (ptr + size + 1))
				return (msh_strdup(ptr + size + 1, shell->mem));
			else
				return (msh_strdup(" ", shell->mem));
		}
		i++;
	}
	return (msh_strdup(" ", shell->mem));
}

static char	*handle_variable(char *var, char *input_line, t_shell *shell, int k)
{
	if (var[0] == '?' && var[1] == '\0')
		return (msh_itoa(g_sig.ret_code, shell->mem));
	else if (check_back_for_heredoc(input_line, k))
		return (msh_strjoin("$", var, shell->mem));
	return (get_content(shell, var));
}

char	**get_vars_content(char *input_line, char **var, t_shell *shell, int k)
{
	char	**vars;
	int		i;

	i = 0;
	vars = msh_malloc(sizeof(char *) * (array_size(var) + 1), shell->mem);
	if (!vars)
		return (free_array(var), NULL);
	while (var[i])
	{
		while (input_line[k] != '$' && input_line[k] != '\0')
		{
			k++;
			if (input_line[k] == '$' && input_line[k + 1] == '$')
				k += 2;
		}
		vars[i] = handle_variable(var[i], input_line, shell, k);
		if (!vars[i])
			return (free_array(var), NULL);
		i++;
		k++;
	}
	vars[i] = NULL;
	return (free_array(var), vars);
}
