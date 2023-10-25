NAME = minishell

CC = cc

CFLAGS =  -Wall -Wextra -Werror -I/Users/cmrabet/.brew/opt/readline/include

SRCS =	parsing_start.c				\
		parsing/ft_isalnum_mini.c	\
		parsing/ft_speechchecker.c	\
		parsing/ft_strtrim_free.c	\
		parsing/ft_splitmini.c		\
		parsing/ft_redirecter.c		\
		parsing/rdp.c				\
		parsing/rdp2.c				\
		parsing/ft_utils.c				\
		parsing/ft_cmd_args.c		\
		parsing/ft_env.c			\
		parsing/ft_env_init.c		\
		execution/builtins/env.c			\
		execution/builtins/cd.c		\
		execution/builtins/pwd.c		\
		execution/builtins/unset.c		\
		execution/builtins/exit.c		\
		execution/builtins/echo.c		\
		execution/builtins/export.c		\
		execution/builtins/export_utils.c		\
		execution/signal.c \
		execution/excute/excute.c \
		execution/excute/find_path.c \
		execution/excute/open_files.c \
		execution/excute/redirection.c \
		execution/excute/heredoc.c		\
		execution/excute/excute2.c		\
		execution/excute/excute3.c		\
		execution/excute/excute_utils.c		\

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

LIBS =	Libft/libft.a

$(NAME): $(OBJS)
	make -C Libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS)  -lreadline -L/Users/cmrabet/.brew/opt/readline/lib -o $(NAME)
	@printf "$(GR)Minishell ready.\n$(RC)"
all: $(NAME)

clean:
	rm -f $(OBJS)
	make -C Libft clean
	@echo "$(RE)Object files removed!$(RC)"

fclean: clean
	rm -f $(NAME)
	make -C Libft fclean
	@echo "$(RE)Removing $(NAME) and .o files "

re: fclean all

# Colors
BA = \033[0;30m
RE = \033[0;31m
GR = \033[0;32m
YE = \033[0;33m
BL = \033[0;34m
PU = \033[0;35m
CY = \033[0;36m
WH = \033[0;37m
RC = \033[0m