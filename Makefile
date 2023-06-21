# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:36:52 by mberrouk          #+#    #+#              #
#    Updated: 2023/06/20 17:34:12 by mberrouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME2 = pipex_bonus

SRC_M	= main.c ft_split.c utils.c pipex.c errors.c

SRC_B	= checks_bonus.c ft_split.c pipex.c utils.c main_bonus.c errors.c here_doc.c pipex_bonus.c

INCLUDE_B = pipex.h pipex_bonus.h

INCLUDE_M = pipex.h

FLAGS	= -Wall -Wextra -Werror

CC		= gcc

all : $(NAME)

$(NAME) : $(SRC_M) $(INCLUDE_M)
	$(CC) $(FLAGS) $(SRC_M) -o $(NAME)

bonus : $(NAME2)

$(NAME2) : $(SRC_B) $(INCLUDE_B)
	$(CC) $(FLAGS) $(SRC_B) -o $(NAME2)

clean :
	@rm -rf $(NAME)

fclean : clean
	@rm -rf $(NAME2)

re : fclean all
