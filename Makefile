CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
NAME = minishell
RL_LIB = -lreadline
RL_PATH = -L /usr/lib
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDE = -I ./includes -I $(LIBFT_DIR) -I /usr/include
RM = rm -rf

SRC_DIR = src

BUILT_DIR = builtins
ENV_DIR = environment
EXPAN_DIR = expansion
SPLIT_DIR = msh_split
PARS_DIR = parsing
UTILS_DIR = utilities
SIG_DIR = signals
EXEC_DIR = executing
EXEC_LIST_DIR = get_exec_list

SRC =	$(SRC_DIR)/$(BUILT_DIR)/msh_cd.c \
		$(SRC_DIR)/$(BUILT_DIR)/msh_echo.c \
		$(SRC_DIR)/$(BUILT_DIR)/msh_env.c \
		$(SRC_DIR)/$(BUILT_DIR)/msh_exit.c \
		$(SRC_DIR)/$(BUILT_DIR)/msh_pwd.c \
		$(SRC_DIR)/$(BUILT_DIR)/msh_export.c \
		$(SRC_DIR)/$(BUILT_DIR)/msh_export2.c \
		$(SRC_DIR)/$(BUILT_DIR)/msh_unset.c \
		$(SRC_DIR)/$(ENV_DIR)/env.c \
		$(SRC_DIR)/$(ENV_DIR)/find_var_value.c \
		$(SRC_DIR)/$(ENV_DIR)/linked_list_to_array.c \
		$(SRC_DIR)/$(ENV_DIR)/set_env_after.c \
		$(SRC_DIR)/$(ENV_DIR)/t_env_management.c \
		$(SRC_DIR)/$(EXPAN_DIR)/count_dollars.c \
		$(SRC_DIR)/$(EXPAN_DIR)/get_final_line.c \
		$(SRC_DIR)/$(EXPAN_DIR)/get_vars_content.c \
		$(SRC_DIR)/$(EXPAN_DIR)/get_vars.c \
		$(SRC_DIR)/$(EXPAN_DIR)/init_line_data.c \
		$(SRC_DIR)/$(EXPAN_DIR)/join_vars.c \
		$(SRC_DIR)/$(SPLIT_DIR)/msh_split_str.c \
		$(SRC_DIR)/$(SPLIT_DIR)/split_str.c \
		$(SRC_DIR)/$(SPLIT_DIR)/msh_split_msh.c \
		$(SRC_DIR)/$(SPLIT_DIR)/split_msh.c \
		$(SRC_DIR)/$(PARS_DIR)/t_cmd_management.c \
		$(SRC_DIR)/$(PARS_DIR)/get_cmd_list.c \
		$(SRC_DIR)/$(PARS_DIR)/tokenization.c \
		$(SRC_DIR)/$(PARS_DIR)/error_management.c \
		$(SRC_DIR)/$(PARS_DIR)/remove_quotes.c \
		$(SRC_DIR)/$(PARS_DIR)/parse_cmd_spc.c \
		$(SRC_DIR)/$(PARS_DIR)/parsing.c \
		$(SRC_DIR)/$(PARS_DIR)/open_heredoc.c \
		$(SRC_DIR)/$(PARS_DIR)/open_heredoc2.c \
		$(SRC_DIR)/$(UTILS_DIR)/utilities1.c \
		$(SRC_DIR)/$(UTILS_DIR)/utilities2.c \
		$(SRC_DIR)/$(UTILS_DIR)/utilities3.c \
		$(SRC_DIR)/$(UTILS_DIR)/quotations.c \
		$(SRC_DIR)/$(UTILS_DIR)/error.c \
		$(SRC_DIR)/$(SIG_DIR)/signalshandling.c \
		$(SRC_DIR)/$(EXEC_LIST_DIR)/fill_in_commands.c \
		$(SRC_DIR)/$(EXEC_LIST_DIR)/get_commands.c \
		$(SRC_DIR)/$(EXEC_LIST_DIR)/t_ex_cmd_management.c \
		$(SRC_DIR)/$(EXEC_LIST_DIR)/t_file_management.c \
		$(SRC_DIR)/$(EXEC_DIR)/executing1.c \
		$(SRC_DIR)/$(EXEC_DIR)/executing2.c \
		$(SRC_DIR)/$(EXEC_DIR)/executing3.c \
		$(SRC_DIR)/$(EXEC_DIR)/execute_cmd.c \
		$(SRC_DIR)/$(EXEC_DIR)/handle_redirections.c \
		$(SRC_DIR)/minishell.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RL_PATH) $(RL_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(OBJ) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

leak: all
	valgrind --leak-check=full \
	--show-leak-kinds=all --track-fds=all --trace-children=yes ./$(NAME)

bash: all
	valgrind --leak-check=full \
	--show-leak-kinds=all --track-fds=all --trace-children=yes bash

.PHONY: all clean fclean re

