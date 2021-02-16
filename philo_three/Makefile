NAME		= philo_three

CC		= gcc
CFLAGS		= -pthread -Werror -Wextra -Wall
FSAN		= -g3 -fsanitize=address
RM		= rm -rf

DIR_SRCS	= srcs/
DIR_OBJS	= objs/
DIR_INC		= .

F_SRCS		= main.c libft_utils.c process_utils.c error.c ft_itoa.c philo_process.c monitor_thread.c
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
