/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:33:55 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 02:39:34 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_var(t_env *list, char *va)
{
	char	**value;

	value = NULL;
	while (list)
	{
		value = ft_split(list->var_name, '=');
		if (ft_strcmp(value[0], va) == 0)
		{
			free_array(value);
			return (ft_strchr(list->var_name, '=') + 1);
		}
		free_array(value);
		if (!list->next)
			return (NULL);
		list = list->next;
	}
	return (NULL);
}

t_env	*find_env_var_index(t_env *list, char *va)
{
	int	len;

	len = ft_strlen(va);
	while (list)
	{
		if (ft_strncmp(list->var_name, va, len) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
