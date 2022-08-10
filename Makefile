CC			= gcc
CFLAGS		= -Werror -Wextra -Wall -g
LIBFLAGS	= -lmlx -framework OpenGL -framework AppKit -L$(LIBFT_DIR) -lft
INCFLAGS	= -I$(INCS_DIR) -I$(LIBFT_INC)

# === Directories === #
SRCS_DIR			:= ./srcs/
OBJS_DIR			:= ./objs/
INCS_DIR			:= ./incs/

SRCS_BONUS_DIR		:= ./srcs_bonus/
OBJS_BONUS_DIR		:= ./objs_bonus/
INCS_BONUS_DIR		:= ./incs_bonus/

LIBFT_DIR			= ./libft/
LIBFT_INC			= $(LIBFT_DIR)includes/
LIBFT_LIB			= libft.a

# === Header files === #
INCS		= $(wildcard $(INCS_DIR)*.h)

# === Define srcs === #
SUBDIRS		:= parse raytrace vec3
S_SUBDIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(SRCS_DIR), $(dir)))
SRCS		= $(wildcard $(SRCS_DIR)*.c) $(foreach dir, $(S_SUBDIRS), $(wildcard $(dir)/*.c))

# === Dfine objs === #
O_SUBDIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(OBJS_DIR), $(dir)))
OBJS		= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

NAME		= miniRT

# === For make bonus === #
ifdef WITH_BONUS
	SRCS_DIR := $(SRCS_BONUS_DIR)
	INCS_DIR := $(INCS_BONUS_DIR)
	OBJS_DIR := $(OBJS_BONUS_DIR)
	SUBDIRS := parse raytrace vec3 texture
endif

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
	$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)[$(NAME)]: done$(RESET)"

bonus : 
	@make WITH_BONUS=1 all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCS_DIR)*.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCFLAGS)
	@echo "\033[2K $(YELLOW)[$(NAME)]: Compiling $< $(RESET)\033[A"

clean :
	@make -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR) $(OBJS_BONUS_DIR)
	@echo "$(RED)[$(NAME)]: clean$(RESET)"

fclean : clean
	@rm -rf $(LIBFT_DIR)$(LIBFT_LIB)
	@echo "$(RED)[$(LIBFT_LIB)]: deleted$(RESET)"
	@rm -rf $(NAME)
	@echo "$(RED)[$(NAME)]: deleted$(RESET)"

re : fclean all

.PHONY : all clean fclean re