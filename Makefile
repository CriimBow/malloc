ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PROJECT = malloc
NAME = libft_malloc_$(HOSTTYPE).so
LIBFT = lft

SRC_NAME =  \
calloc.c \
free.c \
malloc.c \
realloc.c \
show_alloc_free_mem.c \
show_alloc_mem.c \
utils.c \
utils_second.c

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
LFT_PATH = ./libft
INC = -I $(INC_PATH) -I $(LFT_PATH)/includes
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))


CC = gcc
CPPFLAGS = -Iincludes
CFLAGS = -g -fPIC -pthread -Wall -Wextra

all: $(LIBFT) $(NAME)

lft:
	$(MAKE) -C libft

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_PATH)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) -shared $^ -o $@  -Llibft -lft
	rm -f libft_malloc.so
	ln -s $(NAME) libft_malloc.so

clean:
	@$(MAKE) clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C libft
	@rm -f $(NAME) libft_malloc.so

re: fclean all

.PHONY : all, clean, fclean, re, lft
