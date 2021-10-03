NAME = endgame

SRC_DIR = src

INC_DIR = inc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
CC = clang


CFLAGS = -std=c11 
CSFML_LIBS = -lcsfml-system -lcsfml-window -lcsfml-audio -lcsfml-graphics
CSFML_DYLIBS = -L"resource/CSFML/lib" -Wl,-rpath,resource/CSFML/lib
RM = rm -rf

all: $(NAME) clean


$(NAME):
	@$(CC) $(CFLAGS) $(SRC_FILES) -I $(INC_DIR) $(CSFML_DYLIBS) $(CSFML_LIBS) -o $(NAME)
# 	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

clean:
	@$(RM) $(OBJ_DIR)
# 	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@$(RM) $(NAME)
# 	@@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall
