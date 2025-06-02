/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_msh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:39:18 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/01/21 22:59:30 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	inside(char const *s)
{
	char	c;
	int		i;

	i = 0;
	while (*s)
	{
		if ((*s == 39 || *s == 34) && s[1])
		{
			c = *s;
			while (++s && s[1])
			{
				if (*s == '|' || *s == '<' || *s == '>')
				{
					if ((*s == '<' && (*s + 1) == '<') || (*s == '>'
							&& (*s + 1) == '>'))
						s++;
					i++;
				}
				if (*s == c)
					break ;
			}
		}
		s++;
	}
	return (i);
}

static int	count_words(char const *s, int count, int in_word)
{
	if (s[0] == '\0')
		return (1);
	while (*s)
	{
		if (*s == '|' || *s == '<' || *s == '>')
		{
			if ((*s == '<' && (*s + 1) == '<') || (*s == '>'
					&& (*s + 1) == '>'))
				s++;
			in_word = 0;
			count++;
		}
		else if (in_word == 0 && (*s != '|' && *s != '<' && *s != '>'))
		{
			count++;
			in_word = 1;
		}
		s++;
	}
	return (count);
}

char	**msh_split_msh(t_shell *shell)
{
	char	**ptr;
	int		word_count;

	if (!shell->input_line)
		return (NULL);
	word_count = count_words(shell->input_line, 0, 0)
		- inside(shell->input_line);
	ptr = msh_malloc((word_count + 1) * sizeof(char *), shell->mem);
	if (!ptr)
		return (NULL);
	return (split_msh(shell, 0, ptr));
}
