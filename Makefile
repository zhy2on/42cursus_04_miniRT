CC			:= gcc
CFLAGS		:= -Werror -Wextra -Wall $(CHECK)
LIBFLAGS	:= -lmlx -L$(MLX_DIR) -lft -L$(LIBFT_DIR)
INCFLAGS	:= -I$(INC_DIR)
CHECK		:= -fsanitize=address

MLX_DIR = ./mlx/

LIBFT_DIR	:= ./libft/
LIBFT_LIB	:= $(LIBFT_DIR)libft.a
LIBFT_INC	:= $(LIBFT_DIR)includes/
LIBFT		:= $(LIFT_DIR)libft.a

INC_DIR		:= ./incs/
INCLUDES	:= 	minirt.h vec3.h
				
INCS		:= $(addprefix $(INC_DIR), $(INCLUDES))

SRCS_DIR	:=	./srcs/
SOURCES		:=	parsing.c utils.c main.c

SRCS		:=	$(addprefix $(SRCS_DIR), $(SOURCES))

OBJS_DIR	:=	./object/
OBJS		:=	$(SOURCES:.c=.o)
OBJS		:=	$(addprefix $(OBJS_DIR), $(OBJS))

# OBJS_DIR = ./objs/
# OBJECTS		:=	$(SOURCES:.c=.o)
# OBJS = $(addprefix $(OBJS_DIR), $(OBJECTS))

LIBRARY		:= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx
HEADERS		:= -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX_INC)

NAME		:= miniRT

# ----- For make bonus ----- #
ifdef WITH_BONUS
	OBJECTS = $(BONUS_OBJS)
else
	OBJECTS = $(OBJS)
endif

# colors
RED			:=	\033[31m
GREEN 		:=	\033[32m
YELLOW 		:=	\033[33m
BLUE 		:=	\033[34m
MAGENTA		:=	\033[35m
CYAN		:=	\033[36m
WHITE		:=	\033[37m
PINK		:=	\033[38;5;201m
OBJS_DOT	:=	\033[38;5;201m\033[48;5;252m\033[1m\033[3m
MENT		:=	\033[38;5;191m\033[1m
RE_MENT		:=	\033[38;5;63m\033[1m
RESET		:=	\033[0m

.PHONY		: all clean fclean re bonus $(NAME)

$(NAME) : $(OBJECTS)
	@echo $(CLEAN)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) $(OBJECTS) -o $@
	@echo "$(GREEN)[$(NAME)]: done$(RESET)"
#	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
#	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCFLAGS)
	@echo "\033[2K $(YELLOW)[$(NAME)]: Compiling $< $(RESET)\033[A"

all : $(NAME)

clean :
	@make -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)[$(NAME)]: clean$(RESET)"

fclean : clean
	@rm -rf $(LIBFT_DIR)$(LIBFT)
	@echo "$(RED)[$(LIBFT)]: deleted$(RESET)"
	@rm -rf $(NAME)
	@echo "$(RED)[$(NAME)]: deleted$(RESET)"

re : fclean all
