NAME = 	so_long
SRC  :=	$(wildcard ./mandatory/*.c)
SRC_B := $(wildcard ./bonus/*.c)

OBJS        = $(SRC:.c=.o)
OBJS_B      = $(SRC_B:.c=.o)
CC	        = gcc
CFLAGS      = -Wall -Werror -Wextra
#GLFW_FLAGS  = -ldl -lglfw -lm
GLFW_FLAGS = -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ -lm
MLX42_PATH  = ./MLX42
LIBFT_PATH  = ./libft
RM	        = rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: libmlx $(NAME)

libmlx:
	make -C $(MLX42_PATH)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(OBJS) $(LIBFT_PATH)/libft.a $(MLX42_PATH)/libmlx42.a \
	$(GLFW_FLAGS) -o $(NAME)

bonus: libmlx libft $(OBJS_B)
	make -C $(LIBFT_PATH)
	$(CC) $(OBJS_B) $(LIBFT_PATH)/libft.a $(MLX42_PATH)/libmlx42.a \
	$(GLFW_FLAGS) -o $(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX42_PATH) clean
	@$(RM) $(OBJS) $(OBJS_B) && printf "All objects cleaned! :)\n"

fclean:
	make -C $(LIBFT_PATH) fclean
	make -C $(MLX42_PATH) fclean
	@$(RM) $(OBJS) $(OBJS_B) $(NAME) && printf "$(NAME) file cleaned! :)\n"

re: fclean all