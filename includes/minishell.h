/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 01:31:25 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/27 00:31:43 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <linux/limits.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <fcntl.h>

typedef struct s_sig
{
	int			ret_code;
	int			exit_code;
	int			sig;
	int			flag;
}	t_sig;

extern t_sig	g_sig;

typedef enum s_token
{
	Cmd,
	AppendFile,
	HereDocDel,
	Infile,
	Outfile,
	Operation,
	NonOperation,
	Input,
	Output,
	Append,
	HereDoc,
	Pipe,
	None
}	t_token;

typedef struct s_env
{
	char			*var_name;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_cmd
{
	char			**arg;
	t_token			type;
	t_token			op_type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_file
{
	char			*file;
	t_token			file_type;
	struct s_file	*next;
	struct s_file	*prev;
}	t_file;

typedef struct s_exc
{
	char				**cmd;
	t_file				*infile;
	t_file				*outfile;
	struct s_exc		*next;
	struct s_exc		*prev;
}	t_exc;

typedef struct s_shell
{
	int				fd[2];
	int				*pid;
	int				proc_idx;
	int				fd_in;
	char			**env_var;
	char			**commands;
	char			*input_line;
	int				hd;
	t_cmd			*cmd_list;
	t_env			*env_list;
	t_exc			*exec_list;
	t_mem			*mem;
}	t_shell;

typedef struct s_buf
{
	char	*buffer;
	int		vi;
	int		li;
	int		pos;
	int		s;
}	t_buf;

//src/minishell.c
t_shell	*init_minishell(void);
int		data_init(char **argv, t_shell *shell, char **env);
//src//builtins/msh_cd.c
void	msh_cd(t_shell *shell, char **com);
//src//builtins/msh_echo.c
void	msh_echo(char **com, bool flag, int i);
//src//builtins/msh_env.c
void	msh_env(t_env *env_list);
//src//builtins/msh_exit.c
void	msh_exit(t_mem *mem, char **com, int flag);
//src//builtins/msh_export.c
void	msh_export(t_shell *shell, char **com, char c, int i);
char	**sortexport(char **arr, int n);
//src//builtins/msh_export2.c
int		printmyexport(t_shell *shell);
char	**get_key_and_value(char *str, char **ptr, t_mem *mem, int j);
void	print_value(char *str);
char	**get_name(t_mem *mem, char *str);
//src//builtins/msh_pwd.c
void	msh_pwd(t_env *env_list);
//src//builtins/msh_unset.c
t_env	*msh_unset(t_env *list, char **com, t_shell *shell);
//src/environment/env.c
void	dup_env(t_shell *shell, char **env);
void	creat_env_list(t_shell *shell, char **env, int subshell, int i);
//src/environment/find_var_value.c
char	*find_env_var(t_env *list, char *va);
t_env	*find_env_var_index(t_env *list, char *va);
//src/environment/linked_list_to_array.c
char	**linked_list_to_array(t_shell *shell);
int		count_nodes(t_env *list);
//src/environment/set_env_after.c
void	set_env_after_cd(t_shell *shell, char *key, char *value);
void	set_env_if_plus(t_mem *mem, t_env *index, char *export);
void	set_env_after_export(t_shell *shell, char **export, char c,
			bool export_flag);
//src/environment/t_env_management.c
void	lst_env_clear(t_env **list);
t_env	*env_new(t_mem *mem, t_env *list, char *str);
t_env	*env_last(t_env *list);
char	**creat_myenv(t_mem *mem);
//src/expansion/count_dollars.c
int		dollar_is_in(char *str);
int		check_ex(char *str, int size);
//src/expansion/get_final_line.c
char	*get_final_line(char *input_line, t_shell *shell, char **line,
			char **vars);
int		fill_in(char *line, char *ptr, int pos);
//src/expansion/get_vars_content.c
char	**get_vars_content(char *input_line, char **var, t_shell *shell, int k);
char	*get_content(t_shell *shell, char *str);
//src/expansion/get_var.c
char	**get_vars(char *input_line, int k, int j);
//src/expansion/init_line_data.c
t_buf	*init_line_data(char *input_line, t_shell *shell, char **lines,
			char **vars);
//src/expansion/join_vars.c
char	*join_vars(t_mem *mem, char **vars);
//src/msh_split/msh_split_str.c
char	**msh_split_str(char *input_line, t_shell *shell);
//src/msh_split/split_str.c
char	**split_str(char *s1, t_shell *shell, char **ptr, char *start);
char	**ft_free(char **ptr, int i);
//src/msh_split/msh_split_msh.c
char	**msh_split_msh(t_shell *shell);
//src/msh_split/split_msh.c
char	**split_msh(t_shell *shell, int i, char **ptr);
//src/parsing/error_management.c
int		heredoc(t_shell *shell, t_cmd *curr, int i, int heredoc_num);
int		error_management(t_shell *shell, int i);
//src/parsing/get_cmd_list.c
void	get_list(t_shell *shell, int size);
//src/parsing/open_heredoc.c
int		open_heredoc(t_shell *shell, t_cmd *cmd, int pid, int status);
//src/parsing/open_heredoc2.c
void	signal_heredoc(int signum);
void	check_quot_filename(t_mem *mem, bool *flag, char **filename, char *str);
int		print_error(t_mem *mem, int k, char *str);
//src/parsing/parse_cmd_spc.c
int		cmdcheck(char *str);
char	*rm_spaces(t_mem *mem, char *str, int i);
//src/parsing/parsing.c
void	pars_ln(t_shell *shell, int i);
char	*expansion(char *input_line, t_shell *shell);
//src/parsing/remove_quotes.c
void	remove_quotes(t_shell *shell, t_cmd *lst);
size_t	get_size(char *str);
char	*get_string(char *s, t_mem *mem, size_t k, size_t size);
//src/parsing/t_cmd_management.c
void	lstclear(t_cmd **list);
t_cmd	*lstlast(t_cmd *list);
t_cmd	*lstnew(t_mem *mem, char *cmd, t_cmd *list, char **str);
//src/parsing/tokenization.c
void	init_tokens(t_cmd *cmds, int size, t_cmd *list);
//src/signalshandling/signalshandling.c
void	signal_handler(void);
void	ft_handle_sigint(int sig);
void	print_signals_c(int sig);
//src/utilities/error.c
int		error_msg_v1(char *str);
int		error_msg_v2(char *str);
//src/utilities/quotations.c
int		check_quotation(char *str);
//src/utilities/utilities1.c
void	exit_minishell(t_mem *mem, int e);
void	exit_minishell_fd(t_shell *shell, t_exc *cmd, int e);
void	free_array(char **arr);
int		array_size(char	**str);
//src/utilities/utilities2.c
void	msh_close(int fd, char *str);
int		msh_fork(t_mem *mem);
void	msh_clear(t_shell *shell);
//src/utilities/utilities3.c
void	msh_puterror(char *s1, char *s2);
//src/get_exex_list/fill_in_commands.c
void	fill_in_commands(t_shell *sh, t_exc **c, t_file **inf, t_file **outf);
//src/get_exex_list/get_commands.c
t_exc	*get_commands(t_shell *shell);
//src/get_exex_list/t_exc_management.c
t_exc	*command_new(t_mem *mem, t_exc *list);
t_exc	*command_last(t_exc *list);
void	commands_clear(t_exc **list);
int		get_command_size(t_exc *cmd);
//src/get_exex_list/t_file_management.c
void	file_list_clear(t_file **list);
t_file	*last_file_node(t_file *list);
t_file	*new_node(t_mem *mem, t_file *list, char *str, t_token type);
//src/executing/execute_cmd.c
void	exec_cmd_one(char **com, t_exc *command, t_shell *shell,
			char *path);
void	exec_cmd_two(t_exc *cmd, t_shell *shell);
void	exec_cmd_three(char **com, t_exc *c, t_shell *shell, char *path);
//src/executing/executing1.c
int		ex_ln(t_shell *shell);
//src/executing/executing2.c
void	change_(t_shell *shell, t_exc *cmd, char *arg, int i);
int		execute_command(t_exc *command, t_shell *shell, int index);
//src/executing/executing3.c
int		check_bi(char **str);
int		run_builtins(t_shell *shell, t_exc *cmd, int c, int flag);
void	ex_builtins(t_shell *shell, t_exc *list, int builtins);
//src/executing/handle_redirections.c
int		handle_redirection(t_mem *mem, t_exc *cmd_list);

#endif
