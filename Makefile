NAME		= ft_ls
SRCS		= ./srcs/
INCS		= ./incs/
LIBFT_INC	= ./libft/

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror $(INCLUDES) -g
LIBS		= -L ./libft/ -lft -lm

INCLUDES	= -I $(INCS) -I $(LIBFT_INC)

SRC			=	main.c						

OBJS		= $(addprefix $(SRCS), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(OBJS) -o $(NAME) $(LIBS)

clean:
	make -C ./libft clean
	rm -f $(OBJS)
.PHONY: clean

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)
.PHONY: fclean


re: fclean all
.PHONY: re