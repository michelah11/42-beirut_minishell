/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:15:33 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/25 23:02:43 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_2d_size(char **vars, char **lines)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (vars[i])
		size += ft_strlen(vars[i++]);
	i = 0;
	while (lines[i])
		size += ft_strlen(lines[i++]);
	return (size);
}

int	check_double(char *cmd, int i)
{
	while (++i && cmd[i])
	{
		if (cmd[i] == 34)
		{
			i++;
			break ;
		}
	}
	return (i);
}

static void	cmd_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34)
			i = check_double(cmd, i);
		else if (cmd[i] == 39)
		{
			i++;
			while (cmd[i])
			{
				if (cmd[i] == 39)
				{
					i++;
					break ;
				}
				if (cmd[i] == '$')
					cmd[i] = '1';
				i++;
			}
		}
		else
			i++;
	}
}

t_buf	*init_line_data(char *input_line, t_shell *shell,
	char **lines, char **vars)
{
	t_buf	*buf;

	buf = msh_malloc(sizeof(t_buf), shell->mem);
	if (!buf)
		return (NULL);
	buf->vi = 0;
	buf->li = 0;
	buf->pos = 0;
	buf->s = 0;
	buf->buffer = msh_malloc(sizeof(char) * (get_2d_size(vars, lines) + 1),
			shell->mem);
	cmd_check(input_line);
	return (buf);
}
