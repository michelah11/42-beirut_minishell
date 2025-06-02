/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:40:27 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/26 19:31:43 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_in(char *line, char *ptr, int pos)
{
	int	i;
	int	tpos;

	i = 0;
	tpos = pos;
	if (ptr)
	{
		while (ptr[i])
			line[tpos++] = ptr[i++];
	}
	return (tpos);
}

static void	fill_line(t_buf *buf, char **line)
{
	buf->pos = fill_in(buf->buffer, line[buf->li], buf->pos);
	buf->s += ft_strlen(line[buf->li++]);
}

static void	fill_var(t_buf *buf, char **vars, char **line)
{
	buf->pos = fill_in(buf->buffer, vars[buf->vi++], buf->pos);
	buf->s += ft_strlen(line[buf->li++]);
}

char	*get_final_line(char *in_ln, t_shell *shell,
	char **line, char **vars)
{
	t_buf	*buf;

	buf = init_line_data(in_ln, shell, line, vars);
	while (in_ln[buf->s])
	{
		if ((in_ln[buf->s] == '$' && in_ln[buf->s + 1] == 34
				&& !check_ex(in_ln, buf->s)) && line[buf->li])
		{
			fill_line(buf, line);
			buf->vi++;
		}
		else if ((in_ln[buf->s] == '$' && in_ln[buf->s + 1] == 34
				&& check_ex(in_ln, buf->li)) && line[buf->li])
			fill_var(buf, vars, line);
		else if (((in_ln[buf->s] != '$' || in_ln[buf->s + 1] == '$')
				|| (in_ln[buf->s] == '$' && in_ln[buf->s + 1] == '\0'))
			&& line[buf->li])
			fill_line(buf, line);
		else if (in_ln[buf->s] == '$' && in_ln[buf->s + 1] != '\0'
			&& in_ln[buf->s + 1] != '$' && vars[buf->vi]
			&& vars[buf->vi][0] != '\0')
			fill_var(buf, vars, line);
	}
	buf->buffer[buf->pos] = '\0';
	return (buf->buffer);
}
