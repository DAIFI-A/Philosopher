SRCS =	check_args.c ft_atoi.c ft_isdigit.c philosopher.c utils.c tasks.c check_death.c
SRCDIR = mand
OBJS_DIR = objs
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
BONAME = checker
INC = mand/philo.h
OBJS := $(SRCS:%.c=$(OBJS_DIR)/%.o)
BO := $(BONUS:%.c=$(OBJS_BON)/%.o)


all: $(NAME)

$(OBJS_DIR):
			@mkdir $@

$(OBJS_DIR)/%.o: $(SRCDIR)/%.c $(INC) | $(OBJS_DIR)
			$(CC) -c $< -o $@

$(NAME): $(OBJS)
			$(CC) -fsanitize=address $(CFLAGS) $^ -o $(NAME)

clean:
			@rm -rf $(OBJS_DIR) ${OBJS_BON}

fclean:	clean
			@rm -rf  $(NAME)  ${BONAME}

re: fclean all

-include $(DEPS)

.PHONY:	clean re fclean all