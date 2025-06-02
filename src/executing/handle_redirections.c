/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:03:34 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/08 20:47:19 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_files(t_file *file_list)
{
	int	i;

	i = 0;
	while (file_list)
	{
		i++;
		file_list = file_list->next;
	}
	return (i);
}

static void	msh_msh_close(int *fd)
{
	int	i;

	i = 0;
	while (fd && fd[i] != -11)
	{
		if (fd[i] == -1)
			break ;
		msh_close(fd[i], "fd[i]");
		i++;
	}
}

static int	*printerr(int *fd, char *str)
{
	msh_msh_close(fd);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

static int	*msh_open(t_mem *mem, t_file *f_list, int size, int j)
{
	int	*fd;

	size = count_files(f_list);
	fd = msh_malloc((size + 1) * sizeof (int), mem);
	fd[size] = -11;
	while (f_list)
	{
		if (f_list->file_type == Infile)
			fd[j] = open(f_list->file, O_RDONLY);
		else if (f_list->file_type == Outfile)
			fd[j] = open(f_list->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (f_list->file_type == AppendFile)
			fd[j] = open(f_list->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd[j] == -1)
			return (printerr(fd, f_list->file));
		if (f_list->file_type == Infile)
			dup2(fd[j], STDIN_FILENO);
		else if (f_list->file_type == Outfile
			|| f_list->file_type == AppendFile)
			dup2(fd[j], STDOUT_FILENO);
		j++;
		f_list = f_list->next;
	}
	return (fd);
}

int	handle_redirection(t_mem *mem, t_exc *cmd_list)
{
	int	*filein;
	int	*fileout;

	filein = NULL;
	fileout = NULL;
	if (cmd_list->infile)
	{
		filein = msh_open(mem, cmd_list->infile, 0, 0);
		if (!filein)
			return (1);
		msh_msh_close(filein);
	}
	if (cmd_list->outfile)
	{
		if (cmd_list->outfile)
			fileout = msh_open(mem, cmd_list->outfile, 0, 0);
		if (!fileout)
			return (1);
		msh_msh_close(fileout);
	}
	return (0);
}
