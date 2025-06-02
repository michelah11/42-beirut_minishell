/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:06:16 by tayoub            #+#    #+#             */
/*   Updated: 2025/04/03 02:17:40 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**sortexport(char **arr, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
				swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
	return (arr);
}

static int	ft_all_isalpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (msh_isalpha(str[i]) == 1 || str[i] == '_'
			|| str[i] == '+' || str[i] == '	'))
	{
		if (str[i] == '	')
			str[i] = '	';
		i++;
	}
	if ((str[i] == '=' && i != 0) || str[i] == '\0')
		return (0);
	return (1);
}

static char	*fill_var(t_mem *mem, char	*var, char *c)
{
	char	*str;
	int		j;

	*c = '+';
	str = msh_malloc(sizeof(char) * ft_strlen(var), mem);
	j = -1;
	while (++j >= 0 && var[j] != '+')
		str[j] = var[j];
	str[j] = '\0';
	return (str);
}

void	msh_export(t_shell *shell, char **com, char c, int i)
{
	char	**export;
	bool	export_flag;

	if (com[i] == NULL && printmyexport(shell) == 0)
		return ;
	while (com[i])
	{
		c = '-';
		export_flag = false;
		if (ft_all_isalpha(com[i]) == 1)
			printf("export: '%s' :not a valid indentifier\n", com[i]);
		else
		{
			if (com[i][ft_strlen(com[i]) - 1] == '=')
				export_flag = true;
			export = get_key_and_value(com[i], NULL, shell->mem, 0);
			if (export[0][ft_strlen(export[0]) - 1] == '+')
				export[0] = fill_var(shell->mem, export[0], &c);
			set_env_after_export(shell, export, c, export_flag);
		}
		i++;
	}
}
