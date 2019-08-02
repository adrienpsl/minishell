
NAME = minishell

LIBFTDIR = libft/

INCSDIR = includes/

SRCSDIR = src/

OBJSDIR = objs/

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = binary.c \
       builtin.cd.c \
       builtin.echo.c \
       builtin.env.c \
       builtin.env.utils.c \
       builtin.exit.c \
       builtin.setenv.c \
       builtin.unsetenv.c \
       loop.c \
       main.c \
       ms.canonical.c \
       ms.parser.c \
       ms.parser.get_line.c \
       ms.termcaps.c \
       utils.c \


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
