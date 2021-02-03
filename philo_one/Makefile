NAME		= philo_one

CC		= clang
CFLAGS		= -pthread -Werror -Wextra -Wall
FSAN		= -g3 -fsanitize=address
RM		= rm -rf

DIR_SRCS	= srcs/
DIR_OBJS	= objs/
DIR_INC		= .

F_SRCS		= main.c utils.c error.c thread_utils.c
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

clean:
		$(RM) $(DIR_OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:     all re clean fclean fsan
