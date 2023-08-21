NAME= philo
CFLAGS= -Wall -Wextra -Werror #-fsanitize=thread
CC= clang

SRC= philosophers.c \

OBJ= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all