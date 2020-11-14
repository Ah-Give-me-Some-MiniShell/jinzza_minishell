# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 16:34:45 by yujo              #+#    #+#              #
#    Updated: 2020/11/13 20:57:51 by minckim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

# FLAG = -Wall -Wextra -Werror -g

FLAG = -g

# -----------------------------------------------------------------------------
# File names
# -----------------------------------------------------------------------------
FILE_SRCS = \
	minishell\
	check_flag\
	extract_word\
	get_command_line\
	build_exe_tree\
	builtin_env\
	builtin_echo

	# execute_arg\

# -----------------------------------------------------------------------------
# Basic settings
# -----------------------------------------------------------------------------
DIR_COMMON = ./common/
DIR_PARSER = ./parser/
DIR_EXECUTE = ./execute/
DIR_SRCS = ./srcs/
DIR_MINCKIM = ./minckim/
DIR_YUJO = ./yujo/

SRCS = \
	$(addprefix $(DIR_SRCS), $(addsuffix .c, $(FILE_SRCS)))

OBJS = \
	$(addprefix $(DIR_SRCS), $(addsuffix .o, $(FILE_SRCS)))

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

# $(NAME) : print_title $(LIBFT) $(OBJS)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(FLAG) -o $(NAME) $(OBJS) -lft -L$(LIBFT_DIR)
	@echo $(GREEN)"- Done"$(WHITE)

run : $(NAME)
	@./$(NAME)

%.o : %.c
	$(CC) $(FLAG) -c $*.c -o $@

re : fclean $(NAME)

clean :
	@echo $(YELLOW)"Removing minishell object files..."$(WHITE)
	@$(RM) $(OBJS)
	@echo $(YELLOW)"- Done"$(WHITE)
	@make clean -C $(LIBFT_DIR)

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(LIBFT_DIR)libft.a
	@echo $(YELLOW)"Removing minishell object files..."$(WHITE)
	@$(RM) $(NAME)
	@echo $(YELLOW)"- Done"$(WHITE)

leaks:
	@while true; do leaks minishell; sleep 1; done;