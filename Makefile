# --- Nom de votre exécutable ---
NAME = cub3D

# --- Compilateur et Flags ---
# (Le sujet impose 'cc' et ces flags)
CC = cc
CFLAGS = -Wall -Wextra -Werror

# --- Chemins vers les Headers ---
# (Modifiez './includes' si votre .h est ailleurs)
INC_DIRS = -I./includes -I./libft

# --- Fichiers Source (.c) ---
# (Ajoutez TOUS vos fichiers .c ici, séparés par un \)
SRCS =  main.c \
		init.c \
		render.c \
		parse.c \
		parse_texture.c \
		parse_color.c \
		parse_map.c \
		validate_map.c \
		check_walls.c \
		parse_utils.c \
		utils1.c # (J'ai séparé les fonctions logiquement)

# --- Fichiers Objet (.o) ---
# (Généré automatiquement, pas besoin de toucher)
OBJS = $(SRCS:.c=.o)

# --- Bibliothèques ---
# 1. Libft
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# 2. miniLibX (MLX)
# (Décommentez les 2 lignes pour votre OS)

# --- Pour LINUX ---
# (Suppose que mlx est dans /usr/lib et mlx.h dans /usr/include)
MLX_FLAGS = -L/usr/lib -lmlx -lXext -lX11 -lm
INC_DIRS += -I/usr/include
# ---

# --- Pour macOS ---
# (!! Changez /opt/X11 pour le chemin où est installée votre minilibx)
# MLX_PATH = /opt/X11 
# MLX_FLAGS = -L$(MLX_PATH)/lib -lmlx -framework OpenGL -framework AppKit -lm
# INC_DIRS += -I$(MLX_PATH)/include
# ---

# --- Règles de Compilation ---

# Règle par défaut (quand on tape 'make')
all: $(NAME)

# Règle pour créer l'exécutable final
$(NAME): $(OBJS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "cub3D compilé avec succès !"

# Règle pour compiler la libft
$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

# Règle générique pour transformer un .c en .o
%.o: %.c
	@$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

# Nettoie les fichiers objet (.o)
clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "Fichiers objets (.o) nettoyés."

# Nettoie tout (objets + exécutable)
fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "Projet entièrement nettoyé."

# Recompile tout
re: fclean all

# Règle Bonus (requise par le sujet)
# Pour l'instant, elle fait comme 'all'.
bonus: all

# Précise que ces règles ne créent pas de "vrais" fichiers
.PHONY: all clean fclean re bonus