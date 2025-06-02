/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayoub <tayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:25:47 by tayoub            #+#    #+#             */
/*   Updated: 2025/04/03 20:54:09 by tayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_equal_in(char *str)
{
	while (str && *str)
	{
		if (*str == '=')
			return (true);
		str++;
	}
	return (false);
}

static t_env	*remove_node(t_env *head, t_env *node_to_remove)
{
	if (!head || !node_to_remove)
		return (head);
	if (node_to_remove == head)
	{
		head = head->next;
		if (head)
			head->prev = NULL;
		return (head);
	}
	if (node_to_remove->prev)
		node_to_remove->prev->next = node_to_remove->next;
	if (node_to_remove->next)
		node_to_remove->next->prev = node_to_remove->prev;
	return (head);
}

t_env	*msh_unset(t_env *list, char **com, t_shell *shell)
{
	t_env	*index;
	int		i;

	(void) shell;
	i = 0;
	index = NULL;
	while (com[i])
	{
		if (is_equal_in(com[i]) == false)
		{
			index = find_env_var_index(list, com[i]);
			if (index)
				list = remove_node(list, index);
		}
		i++;
	}
	return (list);
}
