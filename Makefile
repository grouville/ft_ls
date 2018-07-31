# Compiler configuration
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror

## Flags for the C preprocessor
CPPFLAGS = -I$(INC_PATH) -Ilibft/

## Libraries path
LDFLAGS = -L$(LIBFT_PATH)

## Libraries to link into the executable
LDLIBS = -lft

## Name of the executable
NAME = ft_ls

# Project related variables
SRC_PATH = srcs
SRC_NAME = boucherie.c\
			print_dev_l_normal_and_fill_struct_flag_l.c\
			sort_and_count_arr.c\
			print_flag_l.c\
			print_folder_flag_l.c\
			print_l_single_arg.c\
			sort_av.c\
			utils.c\
			parse_and_utils_av.c\
			print_and_print_error_av.c
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJS_DIRS = $(sort $(dir $(OBJ)))

INC_PATH = includes
INC_NAME =\
		ft_ls.h\
		libft.h

HEADER = $(addprefix $(INC_PATH)/,$(INC_NAME))

LIBFT_PATH = libft

# Entry point
all: $(NAME)

# Compiles ls
$(NAME): $(LIBFT_PATH)/$(LIBFT_PATH).a $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME) $(LDLIBS)

# Compiles libft/libft.a
# It's a prerequisite to compile ft_ls
$(LIBFT_PATH)/$(LIBFT_PATH).a:
	$(MAKE) -C ./$(LIBFT_PATH)

# Creates obj/ directory
# It's a prerequisite to compile any OBJ
$(OBJS_DIRS):
	mkdir $@

# Adds the dependency to create the directory
# before to compile an object
$(OBJ): | $(OBJS_DIRS)

# Compiles all the src/*.c into obj/*.o
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# /!\ Dirty workaround /!\
# If make on the libft directory should rebuild something then PHONY the rule
# libft to build it. Otherwise it relink.
ifeq ($(shell $(MAKE) --question -C ./$(LIBFT_PATH) ; echo $$?), 1)
.PHONY: $(LIBFT_PATH)/$(LIBFT_PATH).a
endif


.PHONY: clean
clean:
	$(MAKE) -C ./$(LIBFT_PATH) clean
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(MAKE) -C ./$(LIBFT_PATH) fclean
	$(RM) -r $(NAME) $(NAME).dSYM

re: fclean
	$(MAKE) all

.PHONY: norme
norme:
	norminette $(SRC)
	norminette $(INC_PATH)
	norminette $(LIBFT_PATH)/*.c
	norminette $(LIBFT_PATH)/*.h
