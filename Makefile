# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 16:34:45 by yujo              #+#    #+#              #
#    Updated: 2020/11/26 17:39:21 by minckim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAG = -Wall -Wextra -Werror -g

# FLAG = -g

# -----------------------------------------------------------------------------
# File names
# -----------------------------------------------------------------------------
FILE_SRCS = \
	minishell\
	redirection_manage\
	path_finder\
	check_flag\
	extract_word\
	get_command_line\
	build_task_tree\
	execute_task\
	process_terminater\
	builtin_env\
	builtin_cd\
	builtin_pwd\
	builtin_echo\
	builtin_export\
	builtin_unset\
	builtin_exit\
	error_handler

FILE_TESTCASE_SRCS = \
	print_eternally\
	read_nbyte_n_write\
	segmentation_fault\
	loop

# -----------------------------------------------------------------------------
# Basic settings
# -----------------------------------------------------------------------------
DIR_SRCS = ./srcs/
DIR_TESTCASE_SRCS = ./test_case/

SRCS = $(addprefix $(DIR_SRCS), $(addsuffix .c, $(FILE_SRCS)))
OBJS = $(addprefix $(DIR_SRCS), $(addsuffix .o, $(FILE_SRCS)))

TESTCASE_SRCS = $(addprefix $(DIR_TESTCASE_SRCS), $(addsuffix .c, $(FILE_TESTCASE_SRCS)))
TESTCASE_EXE = $(FILE_TESTCASE_SRCS)

LIBFT_DIR = ./libft/
LIBFT = libft.a
INCLUDE = \
	$(DIR_PASER) $(DIR_SRCS)
RM = rm -rf

# -----------------------------------------------------------------------------
# Colors
# -----------------------------------------------------------------------------
BLACK	= "\033[0;30m"
RED		= "\033[0;31m"
GREEN	= "\033[0;32m"
YELLOW	= "\033[0;33m"
BLUE	= "\033[0;34m"
PURPLE	= "\033[0;35m"
CYAN	= "\033[0;36m"
WHITE	= "\033[0;39m"

SLEEPTIME = 0.1

# -----------------------------------------------------------------------------
# Rules
# -----------------------------------------------------------------------------
all : $(NAME)

print_title :
	@clear
	@echo $(RED)
	@cat ./img/ascii_art
	@sleep $(SLEEPTIME)
	@clear
	@echo $(YELLOW)
	@cat ./img/ascii_art
	@sleep $(SLEEPTIME)
	@clear
	@echo $(GREEN)
	@cat ./img/ascii_art
	@sleep $(SLEEPTIME)
	@clear
	@echo $(BLUE)
	@cat ./img/ascii_art
	@sleep $(SLEEPTIME)
	@clear
	@echo $(CYAN)
	@cat ./img/ascii_art
	@sleep $(SLEEPTIME)
	@clear
	@echo $(PURPLE)
	@cat ./img/ascii_art
	@sleep $(SLEEPTIME)
	@echo $(WHITE)
	@clear

$(LIBFT) :
	@make -C $(LIBFT_DIR)

# $(NAME) : $(LIBFT) $(OBJS)

$(NAME) : print_title $(LIBFT) $(OBJS)
	@$(CC) $(FLAG) -o $(NAME) $(OBJS) -lft -L$(LIBFT_DIR)
	@echo $(GREEN)"- Done"$(WHITE)

run : $(NAME)
	@./$(NAME)

$(TESTCASE_EXE) : $(TESTCASE_SRCS)
	gcc $(addprefix $(DIR_TESTCASE_SRCS), $@.c) -o $@

%.o : %.c
	$(CC) $(FLAG) -c $*.c -o $@

re : fclean $(NAME)

clean :
	@echo $(YELLOW)"Removing minishell object files..."$(WHITE)
	@$(RM) $(OBJS)
	@$(RM) $(TESTCASE_EXE)
	@make clean -C $(LIBFT_DIR)

fclean : clean
	@echo $(YELLOW)"Removing libft.a..."$(WHITE)
	@$(RM) $(LIBFT_DIR)libft.a
	@echo $(YELLOW)"Removing minishell..."$(WHITE)
	@$(RM) $(NAME)

test: $(TESTCASE_EXE) ./

leaks:
	@while true; do leaks minishell; sleep 1; done;

norm:
	norminette $(DIR_SRCS)*.c $(DIR_SRCS)*.h
	norminette $(LIBFT_DIR)*.c