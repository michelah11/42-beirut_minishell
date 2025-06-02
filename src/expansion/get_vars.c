/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:29:18 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/25 22:16:07 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*grep_variable_name(char *line, int i, int j)
{
	int		l;
	char	*str;
	int		k;

	l = 0;
	if (!line)
		return (NULL);
	j = ++i;
	if (line[i] && line[i] == '?')
		return (ft_strdup("?"));
	if (line[i] && msh_isalnum(line[i]) != 1)
		i++;
	else
		while (line[i] && msh_isalnum(line[i]) == 1)
			i++;
	k = i - j;
	str = malloc(sizeof(char) * (k + 1));
	if (!str)
		return (NULL);
	while (l < k)
		str[l++] = line[j++];
	str[l] = '\0';
	return (str);
}

char	**get_vars(char *input_line, int k, int j)
{
	char	**var;

	var = malloc(sizeof(char *) * (dollar_is_in(input_line) + 1));
	if (!var)
		return (NULL);
	while (input_line[j])
	{
		if (input_line[j] == 39 && check_ex(input_line, j))
		{
			j++;
			while (input_line[j] && input_line[j] != 39)
				j++;
		}
		if (input_line[j] == '$' && input_line[j + 1] != '\0'
			&& input_line[j + 1] != '$')
			var[k++] = grep_variable_name(input_line + j, 0, 0);
		else if (input_line[j] == '$' && input_line[j + 1] == '$')
			j++;
		if (input_line[j])
		{
			j++;
		}
	}
	var[k] = NULL;
	return (var);
}
