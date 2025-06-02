/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_after.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:43:44 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/04/03 02:19:09 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_after_cd(t_shell *shell, char *key, char *value)
{
	t_env	*index;
	t_env	*node;

	index = find_env_var_index(shell->env_list, key);
	if (index && (ft_strcmp(key, "OLDPWD") == 0 || ft_strcmp(key, "PWD") == 0))
	{
		index->var_name = msh_strjoin(key, "=", shell->mem);
		if (value)
			index->var_name = msh_strjoin(index->var_name, value, shell->mem);
	}
	else if (!index && (ft_strcmp(key, "PWD") == 0 || ft_strcmp(key,
				"OLDPWD") == 0))
	{
		node = env_new(shell->mem, shell->env_list, msh_strjoin(key,
					msh_strjoin("=", value, shell->mem), shell->mem));
		shell->env_list = env_last(shell->env_list);
		shell->env_list->next = node;
	}
}

static bool	check_eq(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	if (j == 0)
		return (true);
	return (false);
}

void	set_env_if_plus(t_mem *mem, t_env *index, char *export)
{
	char	*tmp;

	tmp = index->var_name;
	if (tmp[ft_strlen(tmp) - 1] != '=' && check_eq(tmp))
		index->var_name = msh_strjoin(tmp, msh_strjoin("=", export, mem), mem);
	else
		index->var_name = msh_strjoin(tmp, export, mem);
}

static	char	*msh_str3join(char *s1, char *s2, char *s3, t_mem *mem)
{
	return (msh_strjoin(s1, msh_strjoin(s2, s3, mem), mem));
}

void	set_env_after_export(t_shell *sh, char **exp, char c,
			bool exp_flag)
{
	t_env	*ind;

	ind = find_env_var_index(sh->env_list, exp[0]);
	if (ind)
	{
		if (c == '+')
			set_env_if_plus(sh->mem, ind, exp[1]);
		else
		{
			if (exp[1] || exp_flag == true)
				ind->var_name = msh_strjoin(exp[0], "=", sh->mem);
			if (exp[1])
				ind->var_name = msh_str3join(exp[0], "=", exp[1], sh->mem);
			else if (exp_flag == true)
				ind->var_name = msh_str3join(exp[0], "=", exp[1], sh->mem);
		}
		return ;
	}
	ind = env_last(sh->env_list);
	if (exp_flag == false && exp[1])
		ind->next = env_new(sh->mem, sh->env_list, msh_str3join(exp[0], "=",
					exp[1], sh->mem));
	else
		ind->next = env_new(sh->mem, sh->env_list, msh_strdup(exp[0], sh->mem));
}
