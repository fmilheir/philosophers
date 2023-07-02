NAME = philo
CFLAGS = -Wall -Werror -Werror -fsanitize=thread

SRCS = philo.c philo_utils.c ft_atoi.c routine.c timer.c parsing.c
OBJS =	$(SRCS:.c=.o)
RM =	rm -f

all:	$(NAME)


%.o:	%.c
		@$(CC) $(CFLAGS) -c  $<

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) -pthread $(OBJS) -o $(NAME)
		@tput setaf 90; echo "object files generated"
		@tput setaf 2; echo "philo compiled"


clean:
		@$(RM) $(OBJS)
				@tput setaf 1; echo "object files removed"

fclean:	clean
		@$(RM) $(NAME)
				@tput setaf 1; echo "executable removed"


re:		fclean all

r:
	make re && clear && ./philo 5 800 200 200


#5 800 200 200
#no one should die
#5 600 150 150
#no one should die
#4 410 200 200
#no one should die
#100 800 200 200
#no one should die
#105 800 200 200
#no one should die
#200 800 200 200
#no one should die
