NAME			= philo
CFLAGS			= -Wall -Wextra -Werror
CC				= gcc
HEADER			= philosophers.h
RM				= rm -f

SRCS 			= main.c actions.c init_obj.c
OBJS 			= ${SRCS:.c=.o}


all: 		${NAME}

.c.o:
			${CC} ${CFLAGS}  -c $< -o ${<:.c=.o}

${NAME}: 	$(OBJS) $(HEADER)
			$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re