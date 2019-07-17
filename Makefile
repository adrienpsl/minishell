
NAME = minishell

LIBFTDIR = libft/

INCSDIR = includes/

SRCSDIR = src/

OBJSDIR = objs/

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = builtin.cd.c \
       builtin.echo.c \
       builtin.env.c \
       builtin.env.utils.c \
       builtin.setenv.c \
       builtin.unsetenv.c \
       launch.c \
       main.c \
       parser.c \
       path.c \
       utils.c

OBJS = $(addprefix $(OBJSDIR),$(SRCS:.c=.o))

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -I $(INCSDIR) -I $(LIBFTDIR)$(INCSDIR) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./libft -lft

clean:
	rm -rf $(OBJSDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
