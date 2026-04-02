NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= dinner.c \
			free.c \
			getter_setters.c \
			init.c \
			main.c \
			observer.c \
			philo.c \
			sync.c \
			time.c \
			utils.c \
			utils2.c \
			wrapper.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re 
