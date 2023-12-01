# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 18:20:55 by tnakajo           #+#    #+#              #
#    Updated: 2023/11/28 18:15:57 by tnakajo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo_bonus
INCLUDE		=	-I ./include

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror # -fsanitize=thread
VALGRIND	=	valgrind
RM			=	rm

SRCS_DIR	=	./src/
OBJS_DIR	=	./obj/

SRC_FILES	=	main_bonus \
				open_restaurant_bonus \

SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

VISUALIZER	=	"https://nafuka11.github.io/philosophers-visualizer/"

all:		$(NAME)

$(NAME):	$(OBJS)
#			$(VALGRIND) $(CC) -g $(CFLAGS) $(OBJS) -o $(NAME) # --leak-check=full
			$(CC) -g $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "-----------------------------------------------------------------------------"
			@echo "                                                                             "
			@echo "  ***  *        **                      *                       *     ****** "
			@echo "  *  * *     *   *                      *                      *  *  *    ** "
			@echo "  *  * *         *        ***           *     **        ***   *  *      **   "
			@echo "  ***  ***  **   *   **  *     **  ***  ***  *  * * ** *     *  *     **     "
			@echo "  *    *  *  *   *  *  *  **  *  * *  * *  * ***  **    **   *****   *       "
			@echo "  *    *  *  *   *  *  *    * *  * *  * *  * *    *       *    *   *         "
			@echo "  *    *  * ***  **  **  ***   **  ***  *  *  **  *    ***    *    ****.ph   "
			@echo "                                   *                                         "
			@echo "                                   *                                         "
			@echo "                                   *                                         "
			@echo "-----------------------------------------------------------------------------"
			@echo "  Please enter 4 or 5 arguments  "
			@echo "---------------------------------"
			@echo "   [1][Number of philosophers]   "
			@echo "   [2][Time to die]              "
			@echo "   [3][Time to eat]              "
			@echo "   [4][Time to sleep]            "
			@echo "   [5][Number of meals]          "
			@echo "---------------------------------"
			@echo "Type: % ./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep"
			@echo "Visualizer: " $(VISUALIZER)
			@echo "Example: valgrind --leak-check=full ./philo_bonus 4 310 200 100 2 | grep eating -wc"


#  $(OBJS_DIR)%.o : $(SRCS_DIR)%.c ${INCLUDE}
$(OBJS_DIR)%.o : $(SRCS_DIR)%.c ./include/philo_bonus.h
			@mkdir -p $(@D)
			$(CC) -g $(INCLUDE) -c $< -o $@

clean:
			$(RM) -rf $(OBJS_DIR)

fclean:		clean
			$(RM) -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
