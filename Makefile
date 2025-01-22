# Source files
SRCS =	src/main.c \
		src/free.c \
		src/errors.c \
		src/parse.c \
		src/validate.c \
		src/map.c \

# Object files
OBJS = ${SRCS:.c=.o}

# Target binary name
NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra
#CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
RM = rm -f
LIBFTDIR = lib/ultimate_libft/
LIBFT_LIB = $(LIBFTDIR)/ultimate_libft.a

# Configuración de MLX42
MLX_DIR = lib/MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_INCLUDE = -I$(MLX_DIR)/include
MLX_FLAGS = -ldl -lglfw -pthread -lm

HEADER = include/fdf.h

# Build everything
all: make_libft make_mlx $(NAME)

# Compile .c to .o
.c.o:
	${CC} ${CFLAGS} $(MLX_INCLUDE) -c $< -o $@

# Build the program
$(NAME): $(OBJS) Makefile $(HEADER)
	${CC} ${CFLAGS} $(OBJS) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o ${NAME}


# Build libft
make_libft:
	make -C $(LIBFTDIR)

# Build MLX42
make_mlx:
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	cmake --build $(MLX_DIR)/build

# Clean objects
clean:
	${RM} ${OBJS}
	@cd $(LIBFTDIR) && $(MAKE) clean
	@rm -rf $(MLX_DIR)/build

# Clean all files
fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) clean
	@rm -rf $(MLX_DIR)/build

# Rebuild project
re: fclean all

.PHONY: all clean fclean re