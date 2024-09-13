# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 14:11:23 by melmehdi          #+#    #+#              #
#    Updated: 2024/09/12 16:32:52 by melmehdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

MAINSRCS = $(addprefix ./src/, main.c init_philo.c start_routine.c actions.c start_routine_utils.c lock.c parse_args.c)
UTILSSRCS = $(addprefix ./src/utils/libft/, ft_atoi.c  ft_putstr_fd.c ft_strlen.c ft_isdigit.c)

SRCS = $(MAINSRCS) $(UTILSSRCS)
OBJS = $(SRCS:.c=.o)
NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean :
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all
