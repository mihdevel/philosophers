NAME = philo

SRC_FILES = main.c init_phils.c life_phil.c utils.c monitor.c

OBJ_FILES = $(SRC_FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror
CC= gcc $(FLAGS)

all:$(NAME) $?

%.o: %.c includes/minishell.h
	$(CC) -c $< -o $@

$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME)

clean:
	/bin/rm -f $(OBJ_FILES)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

norm:
	norminette $(SRC_FILES)

.PHONY:	all clean fclean re norm run