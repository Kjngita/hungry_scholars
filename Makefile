NAME = philo

FLAGS = -Wall -Wextra -Werror -pthread -g
HEADER = inc/header_philo.h

S_DIR = src
CFILES = $(S_DIR)/0_main.c \
	$(S_DIR)/1_arg_validation.c \
	$(S_DIR)/2_data_register.c \
	$(S_DIR)/3_threads_start.c \
	$(S_DIR)/4_philos_schedule.c \
	$(S_DIR)/4_supervisor_tasks.c \
	$(S_DIR)/5_wipeout.c

O_DIR = objdir
OFILES = $(CFILES:$(S_DIR)/%.c=$(O_DIR)/%.o)  #$(addprefix $(O_DIR)/,$(CFILES:.c=.o))

all: $(NAME)

$(NAME): $(OFILES)
	cc $(FLAGS) $(OFILES) -o $(NAME)
	@echo "\033[33m** Program created **\033[0m"

$(O_DIR):
	mkdir -p $@

$(O_DIR)/%.o: $(S_DIR)/%.c $(HEADER) | $(O_DIR)
	cc $(FLAGS) -c -Iinc $< -o $@

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