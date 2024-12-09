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
	make -C $(MLX_LINUX)
	$(CC) $(CFLAGS) -I $(INCLUDES) $(OBJS) $(MLX_OS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $(<:.c=.o)

$(MLX_IS)libmlx.a:
	make -C $(MLX_IS) all

clean:
	make -C $(MLX_LINUX) clean
	make -C $(MLX_MAC) clean
	rm -rf $(OBJS) 

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
