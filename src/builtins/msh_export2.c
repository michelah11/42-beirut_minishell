/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:39:57 by tayoub            #+#    #+#             */
/*   Updated: 2025/03/24 20:18:04 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_value(char *str)
{
	while (str && *str && *str != '=')
	{
		printf("%c", *str);
		str++;
	}
	if (str && *str)
	{
		printf("=\"");
		str++;
		while (str && *str)
		{
			printf("%c", *str);
			str++;
		}
		printf("\"");
	}
	printf("\n");
}

char	**get_name(t_mem *mem, char *str)
{
	char	**name;

	name = msh_malloc(sizeof(char *) * 2, mem);
	name[0] = msh_strdup(str, mem);
	name[1] = NULL;
	return (name);
}

int	printmyexport(t_shell *shell)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = linked_list_to_array(shell);
	while (ptr[i])
		i++;
	sortexport(ptr, i);
	i = 0;
	while (ptr[i])
	{
		if (ptr[i][0] == '_' && ptr[i][1] == '=')
			i++;
		else
		{
			printf("declare -x ");
			print_value(ptr[i]);
			i++;
		}
	}
	return (0);
}

char	**get_key_and_value(char *str, char **ptr, t_mem *mem, int j)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	if (j == 0)
		return (get_name(mem, str));
	else
		ptr = msh_malloc(sizeof(char *) * 3, mem);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ptr[0] = msh_malloc(sizeof(char ) * (i + 1), mem);
	j = -1;
	while (++j < i)
		ptr[0][j] = str[j];
	ptr[0][j] = '\0';
	i++;
	ptr[1] = msh_strdup(str + i, mem);
	ptr[2] = NULL;
	return (ptr);
}
