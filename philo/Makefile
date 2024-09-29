NAME = philo
FLAGS =  -g -Wall -Wextra -Werror -pthread -fsanitize=thread
SRC =  philo.c utils.c utils1.c init.c routine.c monitor.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
