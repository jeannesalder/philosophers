NAME		= philo_one

CC		= gcc
CFLAGS		= -pthread -Werror -Wextra -Wall
FSAN		= -g3 -fsanitize=address
RM		= rm -rf

DIR_SRCS	= srcs/
DIR_OBJS	= objs/
DIR_INC		= .

F_SRCS		= main.c libft_utils.c thread_utils.c error.c set_threads.c ft_itoa.c handle_actions.c end_simulation.c
SRCS		= $(addprefix $(DIR_SRCS), $(F_SRCS))

OBJS		= $(addprefix $(DIR_OBJS), $(F_SRCS:.c=.o))

HEADER		= -I $(DIR_INC)

all:		$(NAME)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
		$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(NAME):	$(DIR_OBJS) $(OBJS)
		${CC} $(CFLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJS):
		@mkdir $(DIR_OBJS)

fsan:		$(OBJS)
		${CC} $(CFLAGS) $(FSAN) $(OBJS) -o $(NAME)

val:		$(NAME)
		valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes ./$(NAME) 4 600 400 200

clean:
		$(RM) $(DIR_OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:     all re clean fclean fsan val
