/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:24:24 by tayoub            #+#    #+#             */
/*   Updated: 2025/03/28 23:08:08 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	not_consec_quotes(char *s, int i)
{
	if ((s[i] == '\'' && s[i + 1] && s[i + 1] != '\'')
		|| (s[i] == '\"' && s[i + 1] && s[i + 1] != '\"'))
		return (1);
	return (0);
}

size_t	get_size(char *str)
{
	size_t	k;
	size_t	i;
	char	tmp;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (not_consec_quotes(str, i))
		{
			tmp = str[i];
			i++;
			while (str[i] && str[i + 1] && str[i] != tmp)
				i++;
			k += 2;
		}
		else if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '\"' && str[i + 1] && str[i + 1] == '\"'))
		{
			i++;
			k += 2;
		}
		i++;
	}
	return (i - k);
}

char	*get_string(char *s, t_mem *mem, size_t k, size_t size)
{
	char	*ptr;
	char	tmp;
	size_t	i;

	i = 0;
	ptr = msh_malloc(sizeof(char) * (size + 1), mem);
	while (k < size)
	{
		while (not_consec_quotes(s, i))
		{
			tmp = s[i++];
			while (s[i] && s[i + 1] && s[i] != tmp)
				ptr[k++] = s[i++];
			i++;
		}
		if (k == size)
			break ;
		if ((s[i] == '\'' && s[i + 1] == '\'')
			|| (s[i] == '\"' && s[i + 1] == '\"'))
			i += 2;
		if (s[i] && s[i] != '\'' && s[i] != '\"')
			ptr[k++] = s[i++];
	}
	ptr[k] = '\0';
	return (ptr);
}

void	remove_quotes(t_shell *shell, t_cmd *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->arg && lst->arg[i])
		{
			if (lst->arg[i] != NULL
				&& get_size(lst->arg[i]) != ft_strlen(lst->arg[i]))
				lst->arg[i] = get_string(lst->arg[i], shell->mem, 0,
						get_size(lst->arg[i]));
			i++;
		}
		lst = lst->next;
	}
}
