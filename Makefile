NAME = Dual

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

MLX_LINUX = ./libs/mlx_linux/
MLX_MAC = ./libs/mlx_mac/
INCLUDES = ./headers/

SRCS =

SRCS_MAIN = srcs/main.c

OS_NAME = $(shell uname -s)
CINCLUDES = -I $(INCLUDES)

OBJS = $(SRCS:.c=.o) $(SRCS_MAIN:.c=.o)

MLX_OS = 
ifeq ($(OS_NAME), Linux)
	MLX_IS = $(MLX_LINUX)
	CINCLUDES += -I $(MLX_LINUX)
	MLX_OS += -L $(MLX_LINUX) -lmlx -lXext -lX11 -lm
endif
ifeq ($(OS_NAME), Darwin)
	MLX_IS = $(MLX_MAC)
	CINCLUDES += -I $(MLX_MAC)
	MLX_OS += -L $(MLX_MAC) -lmlx -framework OpenGL -framework Appkit -lm
endif

all: $(NAME)

$(NAME): $(OBJS) $(MLX_IS)libmlx.a
	# Seule la compilation du projet est faite ici, pas la recompilation de libmlx.a
	$(CC) $(CFLAGS) $(CINCLUDES) $(OBJS) $(MLX_OS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $(<:.c=.o)

$(MLX_IS)libmlx.a:
	# Si libmlx.a n'existe pas, lance la compilation de libmlx
	make -C $(MLX_IS) all

clean:
	# Supprimer uniquement les fichiers objets générés par ton projet
	rm -rf $(OBJS)

fclean: clean
	# Supprimer l'exécutable
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
