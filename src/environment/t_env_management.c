/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:05:02 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 01:43:37 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_env_clear(t_env **list)
{
	t_env	*curr;
	t_env	*tmp;

	if (!list || !*list)
		return ;
	curr = *list;
	while (curr->next)
	{
		tmp = curr->next;
		free(curr->var_name);
		free(curr);
		curr = tmp;
	}
	free(curr->var_name);
	free(curr);
	*list = NULL;
}

t_env	*env_last(t_env *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

char	**creat_myenv(t_mem *mem)
{
	char	**env_vars;
	char	buffer[PATH_MAX];

	env_vars = (char **)msh_malloc(4 * sizeof(char *), mem);
	if (!env_vars)
		exit_minishell(mem, 2);
	env_vars[0] = msh_strjoin("PWD=", getcwd(buffer, PATH_MAX), mem);
	env_vars[1] = msh_strdup("SHLVL=1", mem);
	env_vars[2] = msh_strdup("_=/usr/bin/env", mem);
	env_vars[3] = NULL;
	return (env_vars);
}

t_env	*env_new(t_mem *mem, t_env *list, char *str)
{
	t_env	*new_var_node;
	t_env	*last_var_node;

	new_var_node = (t_env *)msh_malloc(sizeof(struct s_env), mem);
	if (!new_var_node)
		return (NULL);
	new_var_node->var_name = str;
	new_var_node->next = NULL;
	if (!list)
		new_var_node->prev = NULL;
	else
	{
		last_var_node = env_last(list);
		new_var_node->prev = last_var_node;
	}
	return (new_var_node);
}
