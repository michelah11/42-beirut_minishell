/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 02:30:25 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/28 22:55:50 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_c(const char *s, char c)
{
	int		i;
	char	tmp;

	i = 0;
	while (s[i] != c && s[i] != '\t' && s[i] != '\0')
	{
		if (s[i] && (s[i] == '\'' || s[i] == '\"' ))
		{
			tmp = s[i++];
			while (s[i] && s[i] != tmp)
				i++;
		}
		i++;
	}
	return (i);
}

static int	count_words(const char *s, char c, int i, int nb)
{
	char	tmp;

	while ((s[i] <= 13 && s[i] >= 9) || s[i] == ' ')
		i++;
	while (s[i] != '\0')
	{
		while (s[i] == c || s[i] == 9)
			i++;
		if (s[i] != '\0')
		{
			nb++;
			while (s[i] != c && s[i] != 9 && s[i] != '\0')
			{
				if (s[i] && (s[i] == '\'' || s[i] == '\"' ))
				{
					tmp = s[i++];
					while (s[i] && s[i] != tmp)
						i++;
				}
				i++;
			}
		}
	}
	return (nb);
}

static void	copy_until_c(char *dest, const char **src, char c)
{
	char	tmp;

	while (**src != c && **src != '\t' && **src != '\0')
	{
		while (**src && (**src == '\'' || **src == '\"' ))
		{
			tmp = **src;
			*dest++ = *(*src)++;
			while (**src && **src != tmp)
				*dest++ = *(*src)++;
			*dest++ = *(*src)++;
		}
		if (**src != c && **src != '\t' && **src != '\0')
			*dest++ = *(*src)++;
	}
	*dest = '\0';
}

static void	free_all(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(str[i++]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

char	**msh_split(char const *s, char c, t_mem *mem)
{
	int			word_nb;
	int			i;
	char		**str;
	const char	*dup;

	word_nb = count_words(s, c, 0, 0);
	str = (char **)msh_malloc(sizeof(char *) * (word_nb + 1), mem);
	if (!str)
		return (NULL);
	dup = s;
	i = 0;
	while (word_nb--)
	{
		while (*dup == c || *dup == '\t')
			dup++;
		str[i] = (char *)msh_malloc(sizeof(char) * (count_c(dup, c) + 1), mem);
		if (!str[i])
		{
			free_all(str, i);
			return (NULL);
		}
		copy_until_c(str[i++], &dup, c);
	}
	str[i] = NULL;
	return (str);
}
