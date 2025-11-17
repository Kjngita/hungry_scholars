NAME = philo

FLAGS = -Wall -Wextra -Werror -pthread -g
HEADER = header_philo.h

CFILES = main.c \
	arg_validation.c \
	init_philos.c \

O_DIR = objdir
OFILES = $(addprefix $(O_DIR)/,$(CFILES:.c=.o))

all: $(NAME)

$(NAME): $(OFILES)
	cc $(FLAGS) $(OFILES) -o $(NAME)
	@echo "\033[33m** Program created **\033[0m"

$(O_DIR):
	mkdir -p $@

$(O_DIR)/%.o: %.c $(HEADER) | $(O_DIR)
	cc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(O_DIR)
	@echo "\033[33m** Object files deleted **\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[33m** Program deleted **\033[0m"

re: fclean all

.SECONDARY: $(OFILES)

.PHONY: all clean fclean re

.SILENT: