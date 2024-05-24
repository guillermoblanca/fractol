NAME := fractol
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g -I$(INC_DIR)/mlx42/include/mlx42

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := inc

MLX42_DIR := $(INC_DIR)/mlx42
MLX42 := $(MLX42_DIR)/libmlx42.a -ldl -lglfw -pthread -lm

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(NAME)
$(NAME): $(OBJ_DIR) $(OBJ) $(MLX42)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX42)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(MLX42):
	cd $(MLX42_DIR) && cmake . && make
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re