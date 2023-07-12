NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

SRCS =	parsing_start.c		\
		ft_isalnum_mini.c	\
		ft_splitmini.c		\
		ft_redirecter.c		\
		rdp.c				\
		ft_cmd_args.c		\
		ft_env.c			\
		ft_env_init.c		\

OBJS = $(SRCS:.c=.o)

CC = gcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

LIBS =	Libft/libft.a

$(NAME): $(OBJS)
	make -C Libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline  -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)
	make -C Libft clean

fclean: clean
	rm -f $(NAME)
	make -C Libft fclean

re: fclean all