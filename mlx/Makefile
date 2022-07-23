


MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-O3

NAME=libmlx.dylib

INC=-I.
#OPTI=-Ounchecked

# === Keywords === #
CLEAN = "\033[2K \033[A"
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	@echo $(CLEAN)
	@swiftc -suppress-warnings $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz -j 100
	@echo "$(GREEN)[$(NAME)]: done$(RESET)"



%.o: %.swift
	@swiftc -suppress-warnings $(OPTI) $(INC) -parse-as-library -c $< -o $@ -j 100
	@echo "\033[2K $(YELLOW)[$(NAME)]: Compiling $< $(RESET)\033[A"

%.swiftmodule: %.swift
	@swiftc -suppress-warnings $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<) -j 100
	@echo "\033[2K $(YELLOW)[$(NAME)]: Compiling $< $(RESET)\033[A"

clean:
	rm -f $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~
	@echo "$(RED)[$(NAME)]: clean$(RESET)"


