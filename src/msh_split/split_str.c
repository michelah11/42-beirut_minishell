/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:48:35 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/26 19:23:03 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*increment_s1(char *s1)
{
	if (*s1 == '\'')
	{
		s1++;
		while (*s1 && *s1 != '\'')
			s1++;
	}
	else
		while (*s1 == '$' && s1[1])
			s1++;
	return (s1);
}

static char	*get_word(char *s1)
{
	if (s1 == NULL )
		return (++s1);
	while (*s1 && (*s1 != '$' || (*s1 == '$' && (!s1[1] || s1[1] == '$'))))
	{
		if (*s1 == '$' && s1[1] == '$')
			s1++;
		s1++;
	}
	return (s1);
}

char	*dup_size(t_mem *mem, const char *start, size_t n)
{
	char	*dup;

	if (n == 0)
		return (NULL);
	dup = (char *)msh_malloc((n + 1) * sizeof(char), mem);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, start, n);
	dup[n] = '\0';
	return (dup);
}

char	**ft_free(char **ptr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(ptr[j++]);
	free(ptr);
	return (NULL);
}

char	**split_str(char *s1, t_shell *shell, char **ptr, char *start)
{
	int		i;

	i = 0;
	while (*s1)
	{
		if (*s1 == '$' && s1[1] && s1[1] != '$')
		{
			start = s1++;
			if (*s1 && ((!msh_isalnum(*s1) && *s1 != 34 && *s1 != 39)
					|| ft_isdigit(*s1) || *s1 == '?'))
				s1++;
			else
				while (*s1 && msh_isalnum(*s1))
					s1++;
			ptr[i++] = dup_size(shell->mem, start, s1 - start);
		}
		else
		{
			start = s1;
			s1 = get_word(s1);
			ptr[i++] = dup_size(shell->mem, start, s1 - start);
		}
	}
	ptr[i] = NULL;
	return (ptr);
}
