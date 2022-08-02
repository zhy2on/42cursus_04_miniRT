CC			= gcc
CFLAGS		= -Werror -Wextra -Wall -g
LIBFLAGS	= -lmlx -framework OpenGL -framework AppKit -L$(LIBFT_DIR) -lft
INCFLAGS	= -I$(INCS_DIR) -I$(LIBFT_INC)
CHECK		= -fsanitize=address

# === For flags === #


# === Directories === #
SRCS_DIR	= ./srcs/
OBJS_DIR	= ./objs/
INCS_DIR	= ./incs/
LIBFT_DIR	= ./libft/
LIBFT_INC	= $(LIBFT_DIR)includes/
LIBFT_LIB	= libft.a

# === Source files === #
SRCS		= main.c utils.c vec3.c parse_figures.c parse_light.c parse_utils.c parse.c \
				cam.c render.c color.c hit.c raytrace.c
#SRCS		= $(wildcard $(dir)/*.c)

# === Header files === #
INC_FILES	= minirt.h vec3.h utils.h
INCS		= $(addprefix $(INCS_DIR), $(INC_FILES))

# === Dfine objects === #
SRC_TO_OBJ	= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJS_DIR), $(SRC_TO_OBJ))

NAME		= miniRT

# === For make bonus === #
#ifdef WITH_BONUS
#	OBJS = $(BONUS_OBJECTS)
#else
#	OBJS = $(OBJECTS)
#endif

# === Keywords === #
CLEAN = "\033[2K \033[A"
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

# === Rules === #
all : $(NAME)

$(NAME) : $(OBJS)
	@echo $(CLEAN)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)[$(NAME)]: done$(RESET)"

bonus : 
	@make WITH_BONUS=1 all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCS_DIR)*.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCFLAGS)
	@echo "\033[2K $(YELLOW)[$(NAME)]: Compiling $< $(RESET)\033[A"

clean :
	@make -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)[$(NAME)]: clean$(RESET)"

fclean : clean
	@rm -rf $(LIBFT_DIR)$(LIBFT_LIB)
	@echo "$(RED)[$(LIBFT_LIB)]: deleted$(RESET)"
	@rm -rf $(NAME)
	@echo "$(RED)[$(NAME)]: deleted$(RESET)"

re : fclean all

.PHONY : all clean fclean re