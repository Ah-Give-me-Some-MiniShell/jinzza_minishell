#Color
BLACK	= "\033[0;30m"
RED		= "\033[0;31m"
GREEN	= "\033[0;32m"
YELLOW	= "\033[0;33m"
BLUE	= "\033[0;34m"
CYAN	= "\033[1;96m"
WHITE	= "\033[0;39m"

CC = gcc
CFLAG = -Wall -Wextra -Werror -g
NAME = libft.a

LIBFT	=\
ft_memset.c		ft_bzero.c		ft_memcpy.c\
ft_memccpy.c	ft_memmove.c	ft_memchr.c\
ft_memcmp.c		ft_strlen.c		ft_strlcpy.c\
ft_strlcat.c	ft_strchr.c		ft_strrchr.c\
ft_strnstr.c	ft_strncmp.c	ft_atoi.c\
ft_isalpha.c	ft_isdigit.c	ft_isalnum.c\
ft_isascii.c	ft_isprint.c	ft_toupper.c\
ft_tolower.c	ft_calloc.c		ft_strdup.c\
\
ft_substr.c		ft_strjoin.c	ft_strtrim.c\
ft_split.c		ft_itoa.c		ft_strmapi.c\
ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c\
ft_putnbr_fd.c\
\
ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c\
ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c\
ft_lstclear.c	ft_lstiter.c		ft_lstmap.c\
\
ft_lstdel_bonus.c		ft_strjoin_free_bonus.c		ft_strinsert_bonus.c\
ft_strcmp_bonus.c		ft_str_new_bonus.c			ft_str_join_free_bonus.c\
ft_str_del_bonus.c		ft_str_append_bonus.c		ft_strcat_bonus.c\
ft_clear_array_bonus.c	ft_lst_strarr_bonus.c		ft_str_get_bonus.c

GNL_DIR = ./get_next_line/
GNL_SRC =\
get_next_line.c get_next_line_utils.c
GNL = $(addprefix $(GNL_DIR),$(GNL_SRC))

PRINTF_DIR = ./ft_printf/
PRINTF_SRC =\
ft_printf.c		ft_printf_util_1.c\
convert_int.c	convert_float1.c	convert_float2.c\
get_option.c	print_d.c			print_u.c\
print_x.c		print_p.c			print_c.c\
print_s.c		print_f.c			print_e.c\
print_g.c		print_n.c
PRINTF = $(addprefix $(PRINTF_DIR),$(PRINTF_SRC))

LIBFT_OBJ = $(LIBFT:.c=.o)
GNL_OBJ = $(GNL:.c=.o)
PRINTF_OBJ = $(PRINTF:.c=.o)
OBJ = $(LIBFT_OBJ) $(GNL_OBJ) $(PRINTF_OBJ)


all : $(NAME)

print_title:
	@echo $(GREEN)"Building Libft, get_next_line, ft_printf..."$(WHITE)

$(NAME) : print_title $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo $(GREEN)"- Done"$(WHITE)

$(OBJ):%.o : %.c
	@$(CC) $(CFLAG) -c -o $@ $*.c

re : fclean all

clean :
	@echo $(YELLOW)"Removing libft object files..."$(WHITE)
	@$(RM) *.o
	@$(RM) $(GNL_DIR)*.o
	@$(RM) $(PRINTF_DIR)*.o

fclean : clean
	@echo $(YELLOW)"Removing libft.a..."$(WHITE)
	@$(RM) $(NAME)

.PHONY: all bonus clean fclean re