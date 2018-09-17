NAME = nibbler

DL1_NAME = dl_sdl.so

DL2_NAME = dl_glfw.so

DL3_NAME = dl_sfml.so


SDIR_MAIN = ./srcs_main/

SDIR_DL1 = ./srcs_sdl/

SDIR_DL2 = ./srcs_glfw/

SDIR_DL3 = ./srcs_sfml/


INCLUDES_DIR = includes


SRC_MAIN = 	$(SDIR_MAIN)MainGame.cpp

SRC_DL1 = 	$(SDIR_DL1)SdlGUI.cpp $(SRC_MAIN)

SRC_DL2 = 	$(SDIR_DL2)GlfwGUI.cpp $(SRC_MAIN)

SRC_DL3 = 	$(SDIR_DL3)SfmlGUI.cpp $(SRC_MAIN)


OBJ_MAIN = $(SRC_MAIN:.cpp=.o)

OBJ_DL1 = $(SRC_DL1:.cpp=.o)

OBJ_DL2 = $(SRC_DL2:.cpp=.o)

OBJ_DL3 = $(SRC_DL3:.cpp=.o)


ALL = $(DL1_NAME) $(DL2_NAME) $(DL3_NAME) $(NAME)


CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES_DIR) -std=c++11

DLFLAGS = $(CFLAGS) -shared -fPIC

DL1_FLAGS = $(DLFLAGS) `pkg-config --libs sdl2`

DL2_FLAGS = $(DLFLAGS) `pkg-config --libs glfw3` -framework OpenGL

DL3_FLAGS = $(DLFLAGS) `pkg-config --libs sfml-all`

CC = clang++

all: $(ALL)

# brew_reset:
# 	rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && export PATH=$HOME/.brew/bin:$PATH && brew update && echo "export PATH=$HOME/.brew/bin:$PATH" >> ~/.zshrc

install:
	brew install pkg-config
	brew install sdl2
	cp -r ~/.brew/Cellar/sdl2/2.0.8/include/ ./$(INCLUDES_DIR)
	brew install glfw
	cp -r ~/.brew/Cellar/glfw/3.2.1/include/GLFW ./$(INCLUDES_DIR)
	brew install sfml
	cp -r ~/.brew/Cellar/sfml/2.4.2_1/include/SFML ./$(INCLUDES_DIR)
	export LD_LIBRARY_PATH=~/.brew/Cellar/sfml/2.4.2_1/lib
	echo "export LD_LIBRARY_PATH=~/.brew/Cellar/sfml/2.4.2_1/lib" >> ~/.zshrc

reinstall_all: brew_reset install
	@echo "				reinstall all"

$(DL1_NAME): $(OBJ_DL1)
	$(CC) $(DL1_FLAGS) -o $(DL1_NAME) $(OBJ_DL1)
	@echo "				$(DL1_NAME) created"

$(DL2_NAME): $(OBJ_DL2)
	$(CC) $(DL2_FLAGS) -o $(DL2_NAME) $(OBJ_DL2)
	@echo "				$(DL2_NAME) created"

$(DL3_NAME): $(OBJ_DL3)
	$(CC) $(DL3_FLAGS) -o $(DL3_NAME) $(OBJ_DL3)
	@echo "				$(DL3_NAME) created"

$(NAME): $(OBJ_MAIN)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_MAIN)
	@echo "				$(NAME) created"

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ_MAIN) $(OBJ_DL1) $(OBJ_DL2) $(OBJ_DL3)
	@echo "				All project's .o deleted"

fclean: clean
	@/bin/rm -f $(ALL)
	@echo "				Exec and libraries deleted"

re: fclean all

.PHONY: all lib clean fclean re