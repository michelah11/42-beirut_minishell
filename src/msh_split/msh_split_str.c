/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:11:38 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/26 19:32:06 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*in_var(char *s1, int *in_word)
{
	s1++;
	if (*s1 == '?')
	{
		s1++;
		*in_word = 0;
	}
	else if (*s1 != '$')
	{
		while (*s1 && msh_isalpha(*s1) && *s1 != '?')
			s1++;
		*in_word = 0;
	}
	return (s1);
}

static int	count_vars(char *s1)
{
	int	count;

	count = 0;
	while (*s1)
	{
		if (*s1 == '$')
		{
			count ++;
			s1++;
			if (*s1 && (!msh_isalnum(*s1) || ft_isdigit(*s1) || *s1 == '?')
				&& *s1 != 34 && *s1 != 39)
				s1++;
			else if (*s1)
				while (*s1 && msh_isalnum(*s1))
					s1++;
		}
		else
		{
			count++;
			while (*s1 && *s1 != '$')
				s1++;
		}
	}
	return (count);
}

char	**msh_split_str(char *input_line, t_shell *shell)
{
	char	**ptr;
	int		word_count;

	if (!input_line)
		return (NULL);
	word_count = count_vars(input_line);
	if (word_count == 0)
		return (NULL);
	ptr = msh_malloc((word_count + 1) * sizeof(char *), shell->mem);
	if (!ptr)
		return (NULL);
	return (split_str(input_line, shell, ptr, NULL));
}
