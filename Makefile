# --- Nom de l'exécutable ---
NAME = cub3D

# --- Compilateur ---
CC = cc
CFLAGS = -Wall -Wextra -Werror

# --- Includes ---
INC_DIRS = -I./includes -I./libft -I./minilibx-linux

# --- Sources ---
SRCS =  main.c \
        init.c \
        render.c \
        parse.c \
        parse_texture.c \
        parse_color.c \
        parse_map.c \
        utils1.c \
        get_next_line/get_next_line.c \
        get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

# --- Libft ---
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a


# --- MiniLibX Linux (version 42) ---
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# --- Couleurs ---
GREEN = \033[1;32m
BLUE  = \033[1;34m
CYAN  = \033[1;36m
RESET = \033[0m

# --- Règles principales ---
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✔ cub3D compilé avec succès !$(RESET)"

$(LIBFT_LIB):
	@make bonus -C $(LIBFT_DIR)


$(MLX_LIB):
	@make -C $(MLX_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@rm -f $(OBJS)
	@echo "$(BLUE)🧹 Fichiers objets supprimés.$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(CYAN)🧹 Projet complètement nettoyé.$(RESET)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
