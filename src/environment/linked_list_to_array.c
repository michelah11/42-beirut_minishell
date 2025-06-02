/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:30:44 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/02/23 01:18:17 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nodes(t_env *list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**linked_list_to_array(t_shell *shell)
{
	char	**s_vars;
	t_env	*current;
	int		count;
	int		i;

	i = 0;
	count = count_nodes(shell->env_list);
	s_vars = (char **)msh_malloc(sizeof(char *) * (count + 1), shell->mem);
	if (!s_vars)
		exit_minishell(shell->mem, EXIT_FAILURE);
	current = shell->env_list;
	while (i < count)
	{
		s_vars[i] = msh_strdup(current->var_name, shell->mem);
		if (!s_vars[i])
		{
			perror("strdup");
			free_array(s_vars);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	s_vars[i] = NULL;
	return (s_vars);
}
