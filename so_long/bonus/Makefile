NAME = 	so_long
SRC  =  main_bonus.c comps_bonus.c create_bonus.c checker_bonus.c moves_bonus.c hook_bonus.c movenem_bonus.c bonus_bonus.c \


OBJS        = $(SRC:.c=.o)
CC	        = gcc
CFLAGS      = -Wall -Werror -Wextra
#GLFW_FLAGS  = -ldl -lglfw -lm
GLFW_FLAGS = -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ -lm
MLX42_PATH  = ./../MLX42
LIBFT_PATH  = ./../libft
RM	        = rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	make -C $(MLX42_PATH)
	$(CC) $(OBJS) $(LIBFT_PATH)/libft.a $(MLX42_PATH)/libmlx42.a \
	$(GLFW_FLAGS) -o $(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX42_PATH) clean
	$(RM) $(OBJS) 

fclean:
	make -C $(LIBFT_PATH) fclean
	make -C $(MLX42_PATH) fclean
	$(RM) $(OBJS) $(NAME)

re: fclean all