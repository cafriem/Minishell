NAME = minishell

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g3 -I/usr/local/opt/readline/include

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
		execution/ft_env.c			\
		execution/builtins/cd.c		\
		execution/builtins/pwd.c		\





OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

LIBS =	Libft/libft.a

$(NAME): $(OBJS)
	make -C Libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -lreadline -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)
	make -C Libft clean

fclean: clean
	rm -f $(NAME)
	make -C Libft fclean

re: fclean all
