CC = cc

CFLAGS = -Werror -Wextra -Wall

SRCS = main.c seating.c utils.c philo_loop.c routine.c waiter.c forks.c \


OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME) 

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:fclean all clean re
