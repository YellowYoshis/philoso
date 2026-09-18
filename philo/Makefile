
NAME			= philo

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -Iinclude -pthread

SRC_DIR			= src
OBJ_DIR			= obj

SRCS			= \
	$(SRC_DIR)/philo.c \
	$(SRC_DIR)/parsing.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/lib.c \
	$(SRC_DIR)/data_init.c \
	$(SRC_DIR)/start.c \
	$(SRC_DIR)/utils_mutex.c \
	$(SRC_DIR)/simulation_ended.c \
	$(SRC_DIR)/action.c \
	$(SRC_DIR)/fork_management.c \

OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "🚀 $(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
#	@$(MAKE) -C clean --no-print-directory
	@echo "🧹 Object files removed."

fclean: clean
	@rm -f $(NAME)
#	@$(MAKE) -C fclean --no-print-directory
	@echo "🗑️  Library and executables removed."

re: fclean all

leaks: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./a.out

.PHONY: all clean fclean re leaks