NAME = cub3d
CC = gcc
INC = /usr/include
INCLIB = $(INC)/minilibx_linux/lib
INCLUDES = ft_cub3d.h
CFLAGS = -Wall -Wextra -Werror -I$(INC) -g -I. -Ilibft

MAC_MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MAC_MINILIBX_DIRECTORY = minilibx_macos
MAC_MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

SRCS = srcs/ft_cub3d.c \
		srcs/ft_initialize.c \
		srcs/ft_draw_utils.c \
		srcs/ft_parser.c

OBJS = $(SRCS:%.c=%.o)

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	# MacOS
	LFLAGS = -lmlx -lm -L$(MAC_MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit
else
	# Linux
	LFLAGS = -Lminilibx_linux -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd
	CFLAGS += -Iminilibx_linux
endif

.c.o: $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	@echo "Building: \033[0;34m$<\033[0m"

$(NAME): $(OBJS) $(INCLUDES)
	@echo "Building: \033[0;34m42libft\033[0m"
	@make -C libft -s
ifneq ($(UNAME), Darwin)
	@echo "Building: \033[0;34mminilibx\033[0m"
	@make -C minilibx_linux -s
endif
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS) libft/libft.a
	@echo "Binary \033[0;32m$(NAME)\033[0m successfully linked!"

all: $(NAME)

clean:
	@make -C minilibx_macos clean -s
ifneq ($(UNAME), Darwin)
	@make -C minilibx_linux clean -s
endif
	@make -C libft clean -s
	@$(RM) $(OBJS)
	@echo "Cleanup: \033[0;34mlinked files\033[0m"

fclean: clean
	@make -C minilibx_macos clean -s
	@$(RM) minilibx_linux/libmlx.a
	@$(RM) minilibx_linux/libmlx_Linux.a
	@make -C libft fclean -s
	@$(RM) $(NAME)
	@echo "Cleanup: \033[0;34mobject files\033[0m"

re: clean all

norminette:
	norminette $(SRCS) $(INCLUDES)
	norminette libft/*.c libft/*.h
	@echo "\033[0;35mAll files in accordance with norminette!\033[0m"

bonus: $(NAME)
