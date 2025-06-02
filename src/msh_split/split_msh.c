/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_msh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:56:49 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/01/16 22:12:13 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_position(char *s)
{
	char	c;

	while (*s && (*s != '|' && *s != '<' && *s != '>'))
	{
		if ((*s == 39 || *s == 34) && s[1])
		{
			c = *s;
			while (++s && s[1] && *s != c)
			{
			}
		}
		s++;
	}
	return (s);
}

char	*ndup(t_mem *mem, char *s, size_t n)
{
	char	*dup;

	if (n == 0)
		return (NULL);
	dup = (char *)msh_malloc((n + 1) * sizeof(char), mem);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}

static int	handle_non_op(t_shell *shell, char **s, char **ptr, int *i)
{
	char	*start;

	start = *s;
	*s = get_position(*s);
	ptr[*i] = ndup(shell->mem, start, *s - start);
	if (!ptr[*i])
	{
		ft_free(ptr, *i);
		return (0);
	}
	(*i)++;
	return (1);
}

static int	handle_op(t_shell *shell, char **s, char **ptr, int *i)
{
	int	k;

	k = 1;
	if ((*s[0] == '<' && *(*s + 1) == '<') || (*s[0] == '>'
			&& *(*s + 1) == '>'))
		k++;
	ptr[*i] = ndup(shell->mem, *s, k);
	if (!ptr[*i])
	{
		ft_free(ptr, *i);
		return (0);
	}
	*s += k;
	(*i)++;
	return (1);
}

char	**split_msh(t_shell *shell, int i, char **ptr)
{
	char	*s;

	s = shell->input_line;
	while (*s)
	{
		if (*s != '|' && *s != '<' && *s != '>')
		{
			if (!handle_non_op(shell, &s, ptr, &i))
				return (NULL);
		}
		else
		{
			if (!handle_op(shell, &s, ptr, &i))
				return (NULL);
		}
	}
	ptr[i] = NULL;
	return (ptr);
}
